#ifndef CMS_COMMANDPARSER_H
#define CMS_COMMANDPARSER_H

#include <tr1/memory>
#include "Command.hpp"
#include "DealerManager.hpp"

namespace cms
{

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