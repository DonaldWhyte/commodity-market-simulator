#ifndef CMS_COMMANDPARSEFUNCTIONS_H
#define CMS_COMMANDPARSEFUNCTIONS_H

#include <vector>
#include <sstream>
#include "PostCommand.hpp"
#include "RevokeCommand.hpp"
#include "CheckCommand.hpp"
#include "ListCommand.hpp"
#include "ParseException.hpp"
#include "Util.hpp"

namespace cms
{	

	// Command type specific parse functions
	CommandPtr parsePostCommand(const std::string& dealerID,
		const std::vector<std::string>& args)
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
		const std::vector<std::string>& args)
	{
		OrderID id = util::toInt(args[0]);	
		return CommandPtr( new RevokeCommand(dealerID, id) );
	}

	CommandPtr parseCheckCommand(const std::string& dealerID,
		const std::vector<std::string>& args)
	{
		OrderID id = util::toInt(args[0]);	
		return CommandPtr( new CheckCommand(dealerID, id) );
	}

	CommandPtr parseListCommand(const std::string& dealerID,
		const std::vector<std::string>& args)
	{
		std::string commodityFilter = (args.size() > 0) ? args[0] : "";
		std::string dealerFilter = (args.size() > 1) ? args[1] : "";
		Command* listCommand = new ListCommand(dealerID, commodityFilter, dealerFilter);
		return CommandPtr(listCommand);	
	}

	CommandPtr parseAggressCommand(
		const std::string& dealerID, const std::vector<std::string>& args)
	{
		return CommandPtr( reinterpret_cast<Command*>(NULL) );	
	}


}

#endif