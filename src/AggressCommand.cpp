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
		// TODO: actually implement
		std::stringstream stream;
		for (unsigned int i = 0; (i < ordersToAggress.size()); i++)
		{
			stream << ordersToAggress[i].first << " " << ordersToAggress[i].second << "\n";
		}
		return stream.str();
	}

}