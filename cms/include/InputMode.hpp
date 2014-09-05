#ifndef CMS_INPUTMODE_H
#define CMS_INPUTMODE_H

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "CommandParser.hpp"
#include "OrderManager.hpp"

namespace cms
{

	/*
	 * Interface: InputMode
	 * Description: Interface implemented by each input mode.
	 * This means input modes can be plugged-and-played into
	 * the main CMS application.
	*/
	class InputMode
	{

	public:
		virtual void run(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser) = 0;

	};

}

#endif