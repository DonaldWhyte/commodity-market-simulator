#ifndef CMS_BASEINPUTMODE_H
#define CMS_BASEINPUTMODE_H

#include "InputMode.hpp"

namespace cms
{
	
	class BaseInputMode : public InputMode
	{

	public:
		virtual void run(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser);
		
	};

}

#endif