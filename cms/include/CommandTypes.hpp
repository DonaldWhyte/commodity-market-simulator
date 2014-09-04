#ifndef CMS_COMMANDTYPES_H
#define CMS_COMMANDTYPES_H

#include "Command.hpp"
#include "CommandParseFunctions.hpp"
#include "DealerManager.hpp"
#include <vector>
#include <string>

namespace cms
{

	typedef CommandPtr (*ParseFunction)(
		const std::string&, const std::vector<std::string>&,
		DealerManagerPtr dealerManager);	

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

	/* Retrieve pointer to command type with given name.
	 * If command with given name does not exist, return NULL. */
	const CommandType* getCommandType(const std::string& commandName);

}

#endif