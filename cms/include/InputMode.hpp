#ifndef CMS_INPUTMODE_H
#define CMS_INPUTMODE_H

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "CommandParser.hpp"
#include "OrderManager.hpp"

namespace cms
{

	class InputMode
	{

	public:
		virtual void run(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser) = 0;

	};

}

#endif