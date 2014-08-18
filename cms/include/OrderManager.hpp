#ifndef CMS_ORDERMANAGER_H
#define CMS_ORDERMANAGER_H

#include <boost/shared_ptr.hpp>
#include <map>
#include "Order.hpp"
#include "CMSException.hpp"
#include "Lock.hpp"

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

	typedef boost::shared_ptr<OrderManager> OrderManagerPtr;
	typedef boost::shared_ptr<Lock<OrderManagerPtr> > OrderManagerLockPtr;

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