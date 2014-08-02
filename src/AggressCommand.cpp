#include "AggressCommand.hpp"
#include <sstream> // TODO: remove

namespace cms
{

	AggressCommand::AggressCommand(const std::string& dealerID,
		const std::vector<OrderAggressAmount>& ordersToAggress)
		: Command("AGGRESS", dealerID), ordersToAggress(ordersToAggress)
	{
	}

	AggressCommand::~AggressCommand()
	{
	}

	std::string AggressCommand::execute(OrderManagerPtr orderManager)
	{
		std::stringstream stream;

		for (std::vector<OrderAggressAmount>::const_iterator it = ordersToAggress.begin();
			(it != ordersToAggress.end()); it++)
		{
			try
			{
				executeAggress(orderManager, *it);
				// Add trade report of successful purchase to output
				const Order& order = orderManager->getOrder(it->first);
				std::string action = "";
				switch (order.side())
				{
				case SIDE_BUY: // sold contracts for a BUY order
					action = "SOLD";
					break;
				case SIDE_SELL: // bought contracts for a SELL order
					action = "BOUGHT";
					break;
				}
				stream << action << " " << it->second
					<< " " << COMMODITY_STRINGS[order.commodity()]
					<< " @ " << order.price()
					<< " FROM " << order.dealerID() << "\n";
			}
			catch (const OrderException& ex)
			{
				stream << ex.what() << "\n";
			}
		}

		return stream.str();
	}

	void AggressCommand::executeAggress(OrderManagerPtr orderManager, const OrderAggressAmount& orderAggress)
	{
		orderManager->sellContracts(orderAggress.first, orderAggress.second);
	}

}