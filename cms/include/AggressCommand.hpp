#ifndef CMS_AGGRESSCOMMAND_H
#define CMS_AGGRESSCOMMAND_H

#include "Command.hpp"
#include <vector>
#include <utility>

namespace cms
{

	/*
	 * NOTE: In the CMS specification, how the trade reports
	 * of several aggressions are displayed to the user has
	 * not been specified. Therefore, an assumption has been
	 * made about the output format of multiple aggressions.
	 *
	 * When contracts from several orders are bought/sold, a
	 * TRADE_REPORT string for each order is generated. These
	 * are separated by newlines when they are displayed to
	 * the user.
	*/

	typedef std::pair<OrderID, unsigned int> OrderAggressAmount;

	/*
	 * Class: AggressCommand
	 * Description: This class executes the logic required to
	 * to execute an AGGRESS command.
	*/
	class AggressCommand : public Command
	{

	public:
		AggressCommand(const std::string& dealerID, const OrderAggressAmount& ordersToAggress);
		AggressCommand(const std::string& dealerID, const std::vector<OrderAggressAmount>& ordersToAggress);
		virtual ~AggressCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

		const std::vector<OrderAggressAmount>& allOrdersToAggress() const;

	private:
		void executeAggress(OrderManagerPtr orderManager,
			const OrderAggressAmount& orderAggress);

		std::vector<OrderAggressAmount> ordersToAggress;

	};

}

#endif