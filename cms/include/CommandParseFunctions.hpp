#ifndef CMS_COMMANDPARSEFUNCTIONS_H
#define CMS_COMMANDPARSEFUNCTIONS_H

#include <vector>
#include <string>
#include "Command.hpp"
#include "DealerManager.hpp"

namespace cms
{	

	// Command type specific parse functions
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