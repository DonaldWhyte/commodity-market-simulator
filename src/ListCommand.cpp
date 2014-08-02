#include "ListCommand.hpp"
#include "DealerManager.hpp"
#include "CMSException.hpp"
#include <sstream>

namespace cms
{

	/* Return string which lists information about all of the
	 * orders with the given IDs (as stored in the given OrderCollection).
	 * Each order is separated by a new line in the string. */
	std::string constructOrderListString(const OrderCollection& orders)
	{
		std::stringstream stream;
		if (orders.size() > 0)
		{
			// Convert first order to string -- no need for a newline!
			OrderCollection::const_iterator order = orders.begin();
			stream << order->first << " " << order->second.toString();
			order++;
			// Convert remaining orders, separating them my newlines
			for (order; (order != orders.end()); order++)
			{
				stream << "\n  " << order->first << " " << order->second.toString();
			}
		}
		return stream.str();	
	}

	void removeOrdersByID(OrderCollection& orders, const std::vector<OrderID>& idsToRemove)
	{
		for (std::vector<OrderID>::const_iterator id = idsToRemove.begin(); (id != idsToRemove.end()); id++)
		{
			orders.erase(orders.find(*id));
		}		
	}

	ListCommand::ListCommand(const std::string& dealerID,
		const std::string& commodityFilter, const std::string& dealerFilter)
		: Command("LIST", dealerID), dealerToList(dealerFilter)
	{
		// If non-existent dealer was given as filter, throw exception!
		if (false) // TODO: implement!!!
		{
			throw CMSException("UNKNOWN_DEALER");
		}
		// If a commodity to filter by has been given
		if (commodityFilter.empty())
		{
			commodityToList = COMMODITY_UNKNOWN;
		}
		else
		{
			commodityToList = toCommodity(commodityFilter);
		}
	}

	ListCommand::~ListCommand()
	{
	}

	std::string ListCommand::execute(OrderManagerPtr orderManager)
	{
		// Initially select all orders
		OrderCollection ordersToList = orderManager->allOrders();
		// Apply list filters and return information on remaining orders
		if (commodityToList != COMMODITY_UNKNOWN)
		{
			filterByCommodity(ordersToList, commodityToList);
		}
		if (!dealerToList.empty())
		{
			filterByDealer(ordersToList, dealerToList);
		}
		return constructOrderListString(ordersToList);
	}

	void ListCommand::filterByCommodity(OrderCollection& orders, Commodity commodity)
	{
		// Find IDs of all orders that DO NOT MATCH FILTER
		std::vector<OrderID> idsToRemove;
		for (OrderCollection::const_iterator order = orders.begin(); (order != orders.end()); order++)
		{
			if (order->second.commodity() != commodity)
			{
				idsToRemove.push_back(order->first);
			}			
		}
		removeOrdersByID(orders, idsToRemove);
	}

	void ListCommand::filterByDealer(OrderCollection& orders, const std::string& dealerID)
	{
		// Find IDs of all orders that DO NOT MATCH FILTER
		std::vector<OrderID> idsToRemove;
		for (OrderCollection::const_iterator order = orders.begin(); (order != orders.end()); order++)
		{
			if (order->second.dealerID() != dealerID)
			{
				idsToRemove.push_back(order->first);
			}			
		}
		removeOrdersByID(orders, idsToRemove);
	}

}