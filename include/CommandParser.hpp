#ifndef CMS_COMMANDPARSER_H
#define CMS_COMMANDPARSER_H

#include <tr1/memory>
#include "Command.hpp"

namespace cms
{

	class CommandParser
	{

	public:
		CommandPtr parse(const std::string& commandStr) const;

	};

}

#endif