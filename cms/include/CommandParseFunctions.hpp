#ifndef CMS_COMMANDPARSEFUNCTIONS_H
#define CMS_COMMANDPARSEFUNCTIONS_H

#include <vector>
#include <string>
#include "Command.hpp"
#include "DealerManager.hpp"

/*
 * DESCRIPTION: Contains functions used to parse individual types
 * of commands. CommandTypes.hpp links these functions to the correct
 * command types. The functions are called by the CommandParser class.
*/
namespace cms
{	

	CommandPtr parsePostCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager);

	CommandPtr parseRevokeCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager);

	CommandPtr parseCheckCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager);

	CommandPtr parseListCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager);

	CommandPtr parseAggressCommand(const std::string& dealerID,
		const std::vector<std::string>& args,
		DealerManagerPtr dealerManager);

}

#endif