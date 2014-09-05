#ifndef CMS_BASEINPUTMODE_H
#define CMS_BASEINPUTMODE_H

#include "InputMode.hpp"

namespace cms
{
	
	/*
	 * CLASS: BaseInputMode
	 * DESCRIPTION: Accepts user input (i.e. CMS commands) from
	 * the command line (via stdin) and outputs the results of
	 * those commands using stdout.
	*/
	class BaseInputMode : public InputMode
	{

	public:
		virtual void run(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser);
		
	};

}

#endif