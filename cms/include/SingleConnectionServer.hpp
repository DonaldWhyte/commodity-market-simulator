#ifndef CMS_SINGLECONNECTIONSERVER_H
#define CMS_SINGLECONNECTIONSERVER_H

#include "InputMode.hpp"

namespace cms
{
	
	class SingleConnectionServer : public InputMode
	{

	public:
		SingleConnectionServer(int port);
		
		virtual void run(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);

	private:
		// Port that the server will listen on
		int port;
		
	};

}

#endif