#ifndef CMS_INPUTMODE_H
#define CMS_INPUTMODE_H

#include <iostream>
#include <tr1/memory>
#include "CommandParser.hpp"
#include "OrderManager.hpp"

namespace cms
{

	class InputMode
	{

	public:
		virtual void run(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser) = 0;

	};

}

#endif