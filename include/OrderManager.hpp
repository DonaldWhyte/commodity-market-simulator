#ifndef CMS_ORDERMANAGER_H
#define CMS_ORDERMANAGER_H

#include <tr1/memory>
#include <map>
#include "Order.hpp"
#include "CMSException.hpp"

namespace cms
{

	typedef unsigned int OrderID;
	typedef std::map<OrderID, Order> OrderCollection;

	class OrderManager
	{
		
	public:
		OrderManager(const OrderCollection& initialOrders = OrderCollection());

		OrderID postOrder(const Order& newOrder); // returns ID of newly added order
		bool revokeOrder(OrderID orderID); // returns false if order with given ID is not posted
		const Order& getOrder(OrderID orderID) const;

		const void sellContracts(OrderID orderID, int amountToSell);
		const OrderCollection& allOrders() const;

	private:
		Order& getOrderByID(OrderID orderID); // throws exception if order with given ID does not exist

		OrderCollection orders;
		OrderID idCounter; // used to generate order IDs

	};

	typedef std::tr1::shared_ptr<OrderManager> OrderManagerPtr;

	class OrderException : public CMSException
	{

	public:
		OrderException(const std::string& message) : CMSException(message)
		{
		}

		virtual ~OrderException() throw()
		{
		}

	};

}

#endif