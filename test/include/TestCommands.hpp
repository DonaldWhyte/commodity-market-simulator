#ifndef CMS_TEST_COMMANDS_H
#define CMS_TEST_COMMANDS_H

#include <gtest/gtest.h>
#include "CommandTypes.hpp"
#include "OrderManager.hpp"
#include "AggressCommand.hpp"
#include "CheckCommand.hpp"
#include "ListCommand.hpp"
#include "PostCommand.hpp"
#include "RevokeCommand.hpp"

namespace cms
{

	namespace test
	{

		TEST(CommandTypeTests, TypeRetrieval)
		{
			// Command which exists
			const CommandType* type = getCommandType("POST");
			ASSERT_FALSE(type == NULL);
			EXPECT_EQ("POST", type->name);
			// Non-existent command
			ASSERT_EQ(NULL, getCommandType("HAHAHAHA"));
		}

		class CommandTests : public ::testing::Test
		{

		public:

			void SetUp()
			{
				orderManager = OrderManagerPtr(new OrderManager());
				orderManagerLock = OrderManagerLockPtr(
					new Lock<OrderManagerPtr>(orderManager)
				);
				// Test orders
				orderManager->postOrder(
					Order("DB", SIDE_BUY, COMMODITY_GOLD, 10000, 22.2));
				orderManager->postOrder(
					Order("HSBC", SIDE_SELL, COMMODITY_SILVER, 200000, 12.424));
			}			

			void TearDown()
			{
				// Delete order manager and its lock that was used for the test
				orderManager = OrderManagerPtr();
				orderManagerLock = OrderManagerLockPtr();
			}

		protected:
			OrderManagerLockPtr orderManagerLock;
			OrderManagerPtr orderManager;

		};

		TEST_F(CommandTests, Aggress)
		{
			// Invalid order given
			OrderAggressAmount invalidAggress(3, 1000);
			AggressCommand command("RBS", invalidAggress);

			ASSERT_EQ(command.run(orderManagerLock),
				"Order with ID '3' does not exist\nEND OF AGGRESS");

			// Aggressing single order
			OrderAggressAmount validAggress(0, 1000);
			command = AggressCommand("RBS", validAggress);

			ASSERT_EQ(10000, orderManager->getOrder(0).amount());
			ASSERT_EQ(command.run(orderManagerLock),
				"SOLD 1000 GOLD @ 22.2 FROM DB\nEND OF AGGRESS");
			ASSERT_EQ(9000, orderManager->getOrder(0).amount());

			// Aggressing multiple orders
			std::vector<OrderAggressAmount> multipleAggressions;
			multipleAggressions.push_back(OrderAggressAmount(0, 50));
			multipleAggressions.push_back(OrderAggressAmount(1, 25234));
			command = AggressCommand("RBS", multipleAggressions);

			ASSERT_EQ(9000, orderManager->getOrder(0).amount());
			ASSERT_EQ(200000, orderManager->getOrder(1).amount());
			ASSERT_EQ(command.run(orderManagerLock),
				"SOLD 50 GOLD @ 22.2 FROM DB\nBOUGHT 25234 SILV @ 12.424 FROM HSBC\nEND OF AGGRESS");
			ASSERT_EQ(8950, orderManager->getOrder(0).amount());
			ASSERT_EQ(174766, orderManager->getOrder(1).amount());

			// Trying to buy/sell more contracts than are available
			OrderAggressAmount tooManyContracts(0, 1000000);
			command = AggressCommand("RBS", tooManyContracts);

			ASSERT_EQ(8950, orderManager->getOrder(0).amount());
			ASSERT_EQ(command.run(orderManagerLock),
				"Requested contracts to buy/sell exceeds available contracts\nEND OF AGGRESS");
			ASSERT_EQ(8950, orderManager->getOrder(0).amount());
		}

		TEST_F(CommandTests, Check)
		{
			// Invalid order
			CheckCommand command("RBS", 3);
			EXPECT_EQ("UNKNOWN_ORDER",
				command.run(orderManagerLock));
			// Not authorised to check order
			command = CheckCommand("RBS", 0);
			EXPECT_EQ("UNAUTHORIZED",
				command.run(orderManagerLock));
			// Order with contracts left (authorised)
			command = CheckCommand("DB", 0);
			EXPECT_EQ("0 DB BUY GOLD 10000 22.2",
				command.run(orderManagerLock));
			// Order with no contracts left (authorised)
			orderManager->sellContracts(0, 10000);
			command = CheckCommand("DB", 0);
			EXPECT_EQ("0 HAS BEEN FILLED",
				command.run(orderManagerLock));
		}

		TEST_F(CommandTests, List)
		{
			// Add one extra order for these tests
			orderManager->postOrder(
				Order("HSBC", SIDE_BUY, COMMODITY_GOLD, 100000, 16.354));
			// Dealer manager must be passed to list command
			DealerManagerPtr dealerManager(new DealerManager());

			// No filters
			ListCommand command("RBS", dealerManager);
			EXPECT_EQ("0 DB BUY GOLD 10000 22.2\n1 HSBC SELL SILV 200000 12.424\n2 HSBC BUY GOLD 100000 16.354\nEND OF LIST",
				command.run(orderManagerLock));
			// Filter by commodity (invalid commodity)
			EXPECT_THROW(
				ListCommand("RBS", dealerManager, "HAHA"),
				CMSException
			);
			// Filter by commodity
			command = ListCommand("RBS", dealerManager, "GOLD");
			EXPECT_EQ("0 DB BUY GOLD 10000 22.2\n2 HSBC BUY GOLD 100000 16.354\nEND OF LIST",
				command.run(orderManagerLock));
			// Filter by commodity AND dealer
			command = ListCommand("RBS", dealerManager, "GOLD", "HSBC");
			EXPECT_EQ("2 HSBC BUY GOLD 100000 16.354\nEND OF LIST",
				command.run(orderManagerLock));

			// Filter by commodity (where no orders are for that commodity)
			command = ListCommand("RBS", dealerManager, "PORK");
			EXPECT_EQ("END OF LIST", command.run(orderManagerLock));
			// Filter by commodity AND dealer (with dealer that has no orders)
			command = ListCommand("RBS", dealerManager, "GOLD", "RBS");
			EXPECT_EQ("END OF LIST", command.run(orderManagerLock));

			// Constructing a LIST command which tries to filer by a 
			// non-existent dealer should throw an exception
			EXPECT_THROW(
				ListCommand("RBS", dealerManager, "GOLD", "SUPER_DEALER"),
				CMSException
			);
		}

		TEST_F(CommandTests, Post)
		{
			// Post a new order, ensuring 
			Order newOrder("RBS", SIDE_SELL, COMMODITY_PORK, 54762, 0.05);
			PostCommand command("RBS", newOrder);

			ASSERT_THROW(orderManager->getOrder(2), OrderException);
			EXPECT_EQ("2 RBS SELL PORK 54762 0.05 HAS BEEN POSTED",
				command.run(orderManagerLock));
			EXPECT_EQ("RBS", orderManager->getOrder(2).dealerID());
			EXPECT_EQ(SIDE_SELL, orderManager->getOrder(2).side());
			EXPECT_EQ(COMMODITY_PORK, orderManager->getOrder(2).commodity());
			EXPECT_EQ(54762, orderManager->getOrder(2).amount());
			EXPECT_EQ(0.05, orderManager->getOrder(2).price());
		}

		TEST_F(CommandTests, Revoke)
		{
			// Invalid order
			RevokeCommand command("RBS", 3);
			EXPECT_EQ("UNKNOWN_ORDER", command.run(orderManagerLock));
			// Not authorised to revoke order
			command = RevokeCommand("RBS", 0);
			EXPECT_EQ("UNAUTHORIZED", command.run(orderManagerLock));
			// Valid revocation
			command = RevokeCommand("DB", 0);
			ASSERT_EQ("DB", orderManager->getOrder(0).dealerID()); // ensure order still exists first!
			EXPECT_EQ("0 HAS BEEN REVOKED", command.run(orderManagerLock));
			ASSERT_THROW(orderManager->getOrder(0), OrderException); // ensure order is removed from list
		}

	}

}

#endif