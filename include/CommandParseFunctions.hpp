#ifndef CMS_COMMANDPARSEFUNCTIONS_H
#define CMS_COMMANDPARSEFUNCTIONS_H

#include <vector>
#include <sstream>
#include "PostCommand.hpp"
#include "ParseException.hpp"

namespace cms
{

	// NOTE: These string conversion functions throw ParseExceptions
	// if the strings do not represent valid commodities/sides/numbers
	Commodity toCommodity(const std::string& str)
	{
		for (unsigned int index = 1; (index < NUM_COMMODITIES); ++index)
		{
			if (str == COMMODITY_STRINGS[index])
			{
				return static_cast<Commodity>(index);
			}
		}
		throw ParseException(str + " is not a valid commodity");
	}

	Side toSide(const std::string& str)
	{
		for (unsigned int index = 1; (index < NUM_SIDES); ++index)
		{
			if (str == SIDE_STRINGS[index])
			{
				return static_cast<Side>(index);
			}
		}
		throw ParseException(str + " is not a valid side");
	}

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
		return CommandPtr( reinterpret_cast<Command*>(NULL) );	
	}

	CommandPtr parseAggressCommand(
		const std::string& dealerID, const std::vector<std::string>& args)
	{
		return CommandPtr( reinterpret_cast<Command*>(NULL) );	
	}


}

#endif