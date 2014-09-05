#ifndef CMS_TEST_ORDERMANAGER_H
#define CMS_TEST_ORDERMANAGER_H

#include <gtest/gtest.h>
#include "OrderManager.hpp"

namespace cms
{

	namespace test
	{

		/* Test Order objects are constructed correctly. */
		TEST(OrderTests, OrderConstruction)
		{
			Order order("DB", SIDE_BUY, COMMODITY_GOLD, 10000, 22.2);
			EXPECT_EQ("DB", order.dealerID());
			EXPECT_EQ(SIDE_BUY, order.side());
			EXPECT_EQ(COMMODITY_GOLD, order.commodity());
			EXPECT_EQ(10000, order.amount());
			EXPECT_EQ(22.2, order.price());
		}

		/* NOTE: These tests are similar to the command tests in TestCommands.hpp.
		 * The difference is that these tests use the order manager DIRECTLY,
		 * rather than altering the order state via the command's run() method. */
		class OrderManagerTests : public ::testing::Test
		{

		public:

			void SetUp()
			{
				testOrders.push_back(Order("DB", SIDE_BUY, COMMODITY_GOLD, 10000, 22.2));
				testOrders.push_back(Order("HSBC", SIDE_SELL, COMMODITY_SILVER, 200000, 12.424));

				orderManager = OrderManagerPtr(new OrderManager());
				orderManager->postOrder(testOrders[0]);
				orderManager->postOrder(testOrders[1]);
			}

			void TearDown()
			{
				testOrders.clear();
				orderManager = OrderManagerPtr();
			}

		protected:
			OrderManagerPtr orderManager;
			std::vector<Order> testOrders;

		};

		TEST_F(OrderManagerTests, PostOrder)
		{
			Order newOrder("RBS", SIDE_SELL, COMMODITY_PORK, 54762, 0.05);
			ASSERT_THROW(orderManager->getOrder(3), OrderException);
			EXPECT_EQ(3, orderManager->postOrder(newOrder));
			EXPECT_EQ(newOrder, orderManager->getOrder(3));
		}

		TEST_F(OrderManagerTests, RevokeOrder)
		{
			// Order that exists
			ASSERT_EQ(testOrders[0], orderManager->getOrder(1));
			ASSERT_TRUE(orderManager->revokeOrder(1));
			ASSERT_THROW(orderManager->getOrder(1), OrderException);
			// Non-existent order (the one that was just revoked)
			ASSERT_FALSE(orderManager->revokeOrder(1));
		}

		TEST_F(OrderManagerTests, GetOrder)
		{
			// Order that exists
			ASSERT_EQ(testOrders[0], orderManager->getOrder(1));
			// Non-existent order
			ASSERT_THROW(orderManager->getOrder(3), OrderException);
		}

		TEST_F(OrderManagerTests, SellContracts)
		{
			// Non-existent order
			EXPECT_THROW(orderManager->sellContracts(3, 100), OrderException);
			// Order that exists
			ASSERT_EQ(10000, orderManager->getOrder(1).amount());
			orderManager->sellContracts(1, 1000);
			ASSERT_EQ(9000, orderManager->getOrder(1).amount());
			// Requesting to buy/sell more contracts than available
			EXPECT_THROW(orderManager->sellContracts(1, 2000000), OrderException);
		}

		TEST_F(OrderManagerTests, AllOrders)
		{
			OrderCollection expectedCollection;
			expectedCollection.insert(
				std::pair<OrderID, Order>(1, testOrders[0]));
			expectedCollection.insert(
				std::pair<OrderID, Order>(2, testOrders[1]));
			ASSERT_EQ(expectedCollection, orderManager->allOrders());
		}

	}

}

#endif