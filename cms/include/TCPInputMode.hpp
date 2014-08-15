#ifndef CMS_TCPINPUTMODE_H
#define CMS_TCPINPUTMODE_H

#include "InputMode.hpp"

namespace cms
{
	
	class TCPInputMode : public InputMode
	{

	public:
		TCPInputMode(int port, bool continuousExecution = true);

		virtual void run(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);

	private:
		// If true: server will accept an unlimited number of client requests.
		// If false: server will terminate after accepting ONE client request
		bool continuousExecution;
		// Port that the server will listen on
		int port;
		
	};

}

#endif