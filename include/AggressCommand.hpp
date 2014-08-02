#ifndef CMS_AGGRESSCOMMAND_H
#define CMS_AGGRESSCOMMAND_H

#include "Command.hpp"
#include <vector>
#include <utility>

namespace cms
{

	// TODO: make error messages follow specification
	// TODO: determine how to handle interleaved success/errors
	//       with multiple aggressions (just list all in newlines???)

	typedef std::pair<OrderID, unsigned int> OrderAggressAmount;

	class AggressCommand : public Command
	{

	public:
		AggressCommand(const std::string& dealerID, const std::vector<OrderAggressAmount>& ordersToAggress);
		virtual ~AggressCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

	private:
		void executeAggress(OrderManagerPtr orderManager,
			const OrderAggressAmount& orderAggress);

		std::vector<OrderAggressAmount> ordersToAggress;

	};

}

#endif