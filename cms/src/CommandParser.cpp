#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "DealerManager.hpp"
#include "CommandTypes.hpp"
#include "CommandParser.hpp"
#include "ParseException.hpp"

namespace cms
{

	CommandParser::CommandParser(DealerManagerPtr dealerManager)
		: dealerManager(dealerManager)
	{
	}

	CommandPtr CommandParser::parse(const std::string& commandStr) const
	{
		using namespace std; // to make tokenisation cope more readable

		// Ensure command has not exceeded maximum length
		if (commandStr.length() > MAX_COMMAND_LENGTH)
		{
			std::stringstream errorMessage;
			errorMessage << "Command exceeds maximum length (command length: "
				<< commandStr.length() << ", max length: "
				<< MAX_COMMAND_LENGTH << ")";
			throw ParseException(errorMessage.str());
		}

		// Tokenise command string using whitespace as token delimiters
		vector<string> tokens;
		istringstream stream(commandStr);
		copy(istream_iterator<string>(stream),
     		istream_iterator<string>(),
     		back_inserter<vector<string> >(tokens));

		// At least dealer ID and the command type must be given
		if (tokens.size() < 2)
		{
			throw ParseException("Dealer ID and command type must be given");
		}

		// Check dealer exists in system
		std::string dealerID = tokens[0];
		if (!dealerManager->isValidDealer(dealerID))
		{
			throw ParseException("UNKNOWN_DEALER");
		}

		// Retrieve type object corresponding to the given command type
		std::string typeStr = tokens[1];
		const CommandType* typeObject = getCommandType(typeStr);
		if (!typeObject)
		{
			throw ParseException("INVALID_COMMAND");
		}

		// Remove first two entries of tokens, so only command args remain
		tokens.erase(tokens.begin(), tokens.begin() + 2); // guaranteed to have at least two elements, so this is safe
		// Ensure enough arguments are given
		if (tokens.size() < typeObject->requiredArgs)
		{
			std::stringstream errorMessage;
			errorMessage << typeStr << " requires at least "
				<< typeObject->requiredArgs << " arguments, "
				<< tokens.size() << " given";
			throw ParseException(errorMessage.str());
		}

		return typeObject->parser(dealerID, tokens, dealerManager);
	}

}