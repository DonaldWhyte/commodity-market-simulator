#include "ListCommand.hpp"
#include <sstream>
#include <vector>

namespace cms
{

	ListCommand::ListCommand(const std::string& dealerID,
		const std::string& commodityFilter, const std::string& dealerFilter)
		: Command("LIST", dealerID), dealerToList(dealerFilter)
	{
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
		const OrderCollection& orders = orderManager->allOrders();
		// Initially select all orders
		std::vector<OrderID> ordersToList;
		ordersToList.reserve(orders.size());
		for (OrderCollection::const_iterator it = orders.begin(); (it != orders.end()); it++)
		{
			ordersToList.push_back(it->first);
		}

		// Remove orders without matching commodity
		if (commodityToList != COMMODITY_UNKNOWN) // only if filter provided
		{
			// Done in reverse order to we can remove indices
			// from the vector while iterating through it
			for (int i = ordersToList.size() - 1; (i >= 0); i--)
			{
				// Remove order index if its commodity does not match filter
				OrderID id = ordersToList[i];
				OrderCollection::const_iterator order = orders.find(id);
				if (order->second.commodity() != commodityToList)
				{
					ordersToList.erase(ordersToList.begin() + i);
				}
			}
		}

		// Remove orders without matching dealer ID
		if (!dealerToList.empty())
		{
			for (int i = ordersToList.size() - 1; (i >= 0); i--)
			{
				OrderID id = ordersToList[i];
				OrderCollection::const_iterator order = orders.find(id);
				if (order->second.dealerID() != dealerToList)
				{
					ordersToList.erase(ordersToList.begin() + i);
				}
			}
		}

		// Return list of all matching orders as a string
		std::stringstream stream;
		if (ordersToList.size() > 0)
		{
			// Convert first order to string -- no need for a newline!
			std::vector<OrderID>::const_iterator orderID = ordersToList.begin();
			OrderCollection::const_iterator order = orders.find(*orderID);
			stream << order->first << " " << order->second.toString();
			orderID++;
			// Convert remaining orders, separating them my newlines
			for (orderID; (orderID != ordersToList.end()); orderID++)
			{
				order = orders.find(*orderID);
				stream << "\n  " << order->first << " " << order->second.toString();
			}
		}
		return stream.str();	
	}

}