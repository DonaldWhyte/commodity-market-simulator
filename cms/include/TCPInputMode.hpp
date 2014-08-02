#ifndef CMS_TCPINPUTMODE_H
#define CMS_TCPINPUTMODE_H

#include "InputMode.hpp"

namespace cms
{
	
	class TCPInputMode : public InputMode
	{

	public:
		TCPInputMode(int port);

		virtual void run(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);

	private:
		int port;
		
	};

}

#endif