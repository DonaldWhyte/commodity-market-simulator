#ifndef CMS_COMMANDPARSER_H
#define CMS_COMMANDPARSER_H

#include <boost/shared_ptr.hpp>
#include "Command.hpp"
#include "DealerManager.hpp"

namespace cms
{

	// Maximum number of characters allowed in a single command
	static const unsigned int MAX_COMMAND_LENGTH = 255;

	/*
	 * CLASS: CommandParser
	 * DESCRIPTION: Parses command strings, returning a pointer
	 * to a Command object that can be executed.
	 *
	 * Note that this requires an instance of DealerManager
	 * to ensure any specified dealers are valid.
	*/
	class CommandParser
	{

	public:
		CommandParser(DealerManagerPtr dealerManager);
		CommandPtr parse(const std::string& commandStr) const;

	private:
		DealerManagerPtr dealerManager;

	};

}

#endif