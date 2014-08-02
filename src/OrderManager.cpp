#include "OrderManager.hpp"
#include <sstream>

namespace cms
{

	OrderManager::OrderManager(const OrderCollection& initialOrders)
		: orders(initialOrders), idCounter(initialOrders.size())
	{
	}

	OrderID OrderManager::postOrder(const Order& newOrder)
	{
		OrderID newOrderID = idCounter++;
		orders.insert( std::pair<OrderID, Order>(newOrderID, newOrder) );
		return newOrderID;
	}

	bool OrderManager::revokeOrder(OrderID orderID)
	{
		OrderCollection::iterator foundOrder = orders.find(orderID);
		if (foundOrder != orders.end())
		{
			orders.erase(foundOrder);
			return true;
		}
		else
		{
			return false;
		}
	}

	const Order& OrderManager::getOrder(OrderID orderID) const
	{
		OrderCollection::const_iterator foundOrder = orders.find(orderID);
		if (foundOrder != orders.end())
		{
			return foundOrder->second;
		}
		else
		{
			std::stringstream errorMessage;
			errorMessage << "Order with ID '" << orderID << "' does not exist";
			throw OrderException(errorMessage.str());
		}
	}

	const void OrderManager::sellContracts(OrderID orderID, int amountToSell)
	{
		Order& foundOrder = getOrderByID(orderID);

		bool success = foundOrder.reduceAmount(amountToSell);
		if (!success) // not enough contracts to sell! throw exception
		{
			throw OrderException("Requested contracts to buy exceeds available contracts");
		}
	}

	const OrderCollection& OrderManager::allOrders() const
	{
		return orders;
	}

	Order& OrderManager::getOrderByID(OrderID orderID)
	{
		OrderCollection::iterator foundOrder = orders.find(orderID);
		if (foundOrder != orders.end())
		{
			return foundOrder->second;
		}
		else
		{
			std::stringstream errorMessage;
			errorMessage << "Order with ID '" << orderID << "' does not exist";
			throw OrderException(errorMessage.str());
		}
	}

}