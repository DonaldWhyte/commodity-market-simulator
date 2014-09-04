#include <sstream>
#include "CommandParseFunctions.hpp"
#include "PostCommand.hpp"
#include "RevokeCommand.hpp"
#include "CheckCommand.hpp"
#include "ListCommand.hpp"
#include "AggressCommand.hpp"
#include "Util.hpp"
#include "ParseException.hpp"

namespace cms
{	

	// Command type specific parse functions
	CommandPtr parsePostCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager)
	{
		// Convert string arguments to their correct prototypes
		Side side = toSide(args[0]);
		Commodity commodity = toCommodity(args[1]);
		int amount = util::toPositiveInt(args[2]);
		double price = util::toDouble(args[3]);

		Order orderToPost(dealerID, side, commodity, amount, price);
		return CommandPtr( new PostCommand(dealerID, orderToPost) );
	}

	CommandPtr parseRevokeCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager)
	{
		OrderID id = util::toInt(args[0]);	
		return CommandPtr( new RevokeCommand(dealerID, id) );
	}

	CommandPtr parseCheckCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager)
	{
		OrderID id = util::toInt(args[0]);	
		return CommandPtr( new CheckCommand(dealerID, id) );
	}

	CommandPtr parseListCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager)
	{
		std::string commodityFilter = (args.size() > 0) ? args[0] : "";
		std::string dealerFilter = (args.size() > 1) ? args[1] : "";
		Command* listCommand = new ListCommand(dealerID, dealerManager,
			commodityFilter, dealerFilter);
		return CommandPtr(listCommand);	
	}

	CommandPtr parseAggressCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager)
	{
		std::vector<OrderAggressAmount> ordersToAggress;
		// Arguments should come in pairs of twos, so we iterate
		// through two at a time.
		// NOTE: This means any odd, leftover argument will be ignored
		for (unsigned int i = 0; (i < args.size() - 1); i += 2)
		{
			OrderID orderID = util::toInt(args[i]);
			int amount = util::toPositiveInt(args[i + 1]);
			ordersToAggress.push_back( OrderAggressAmount(orderID, amount) );
		}

		Command* aggressCommand = new AggressCommand(dealerID, ordersToAggress);
		return CommandPtr(aggressCommand);	
	}

}
