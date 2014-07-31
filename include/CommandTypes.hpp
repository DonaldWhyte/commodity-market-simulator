#ifndef CMS_COMMANDTYPES_H
#define CMS_COMMANDTYPES_H

#include "Command.hpp"
#include "CommandParseFunctions.hpp"
#include <vector>
#include <string>

namespace cms
{

	typedef CommandPtr (*ParseFunction)(
		const std::string&, const std::vector<std::string>&);	

	struct CommandType
	{
		std::string name;
		unsigned int requiredArgs;
		ParseFunction parser;
	};

	/* Contains all possible commands in CMS platform.
	 * New commands should be added here. */
	static const CommandType COMMAND_TYPES[] = {
		{ "POST", 4, parsePostCommand },
		{ "REVOKE", 1, parseRevokeCommand },
		{ "CHECK", 1, parseCheckCommand },
		{ "LIST", 0, parseListCommand },
		{ "AGGRESS", 2, parseAggressCommand },
	};
	/* Make sure this number matches the amount of command types
	 * stored in the COMMAND_TYPES array. */
	static const unsigned int NUM_COMMAND_TYPES = 5;

	const CommandType* getCommandType(const std::string& commandName)
	{
		for (unsigned int i = 0; (i < NUM_COMMAND_TYPES); i++)
		{
			if (commandName == COMMAND_TYPES[i].name)
			{
				return &COMMAND_TYPES[i];
			}
		}
		// If this point is reached, no type with given name exists
		return NULL;
	}

}

#endif