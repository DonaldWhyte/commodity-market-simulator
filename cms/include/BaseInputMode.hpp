#ifndef CMS_BASEINPUTMODE_H
#define CMS_BASEINPUTMODE_H

#include "InputMode.hpp"

namespace cms
{
	
	class BaseInputMode : public InputMode
	{

	public:
		virtual void run(OrderManagerLockPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);
		
	};

}

#endif