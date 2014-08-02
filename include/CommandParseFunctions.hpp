#ifndef CMS_COMMANDPARSEFUNCTIONS_H
#define CMS_COMMANDPARSEFUNCTIONS_H

#include <vector>
#include <sstream>
#include "PostCommand.hpp"
#include "ListCommand.hpp"
#include "ParseException.hpp"

namespace cms
{

	int toPositiveInteger(const std::string& str)
	{
		int converted = 0;
		std::istringstream ss(str);
		ss >> converted;
		// Check if there was a parse error
		if (ss.rdstate() & std::ios::failbit)
		{
			throw ParseException("'" + str + "' is not a valid integer");
		}
		// Ensure integer is positive
		if (converted <= 0)
		{
			throw ParseException("'" + str + "' must be a positive integer (> 0)");
		}
		return converted;
	}

	double toDouble(const std::string& str)
	{
		double converted = 0;
		std::istringstream ss(str);
		ss >> converted;
		// Check if there was a parse error
		if (ss.rdstate() & std::ios::failbit)
		{
			throw ParseException("'" + str + "' is not a valid double");
		}

		return converted;
	}

	// Command type specific parse functions
	CommandPtr parsePostCommand(const std::string& dealerID,
		const std::vector<std::string>& args)
	{
		// Convert string arguments to their correct prototypes
		Side side = toSide(args[0]);
		Commodity commodity = toCommodity(args[1]);
		int amount = toPositiveInteger(args[2]);
		double price = toDouble(args[3]);

		Order orderToPost(dealerID, side, commodity, amount, price);
		return CommandPtr( new PostCommand(dealerID, orderToPost) );
	}

	CommandPtr parseRevokeCommand(const std::string& dealerID,
		const std::vector<std::string>& args)
	{
		return CommandPtr( reinterpret_cast<Command*>(NULL) );	
	}

	CommandPtr parseCheckCommand(const std::string& dealerID,
		const std::vector<std::string>& args)
	{
		return CommandPtr( reinterpret_cast<Command*>(NULL) );	
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