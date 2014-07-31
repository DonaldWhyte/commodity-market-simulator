#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "CommandTypes.hpp"
#include "CommandParser.hpp"
#include "ParseException.hpp"

namespace cms
{

	CommandPtr CommandParser::parse(const std::string& commandStr) const
	{
		using namespace std; // to make tokenisation cope more readable

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
		std::string dealerID = tokens[0];
		std::string typeStr = tokens[1];
		// Retrieve type object corresponding to the given command type
		const CommandType* typeObject = getCommandType(typeStr);
		if (!typeObject)
		{
			throw ParseException(typeStr + " is not a valid command");
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

		return typeObject->parser(dealerID, tokens);
	}

}