#ifndef CMS_AGGRESSCOMMAND_H
#define CMS_AGGRESSCOMMAND_H

#include "Command.hpp"
#include <vector>
#include <utility>

namespace cms
{

	typedef std::pair<OrderID, unsigned int> OrderAggressAmount;

	class AggressCommand : public Command
	{

	public:
		AggressCommand(const std::string& dealerID, const std::vector<OrderAggressAmount>& ordersToAggress);
		virtual ~AggressCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

	private:
		std::vector<OrderAggressAmount> ordersToAggress;

	};

}

#endif