#ifndef CMS_MULTITHREADEDSERVER_H
#define CMS_MULTITHREADEDSERVER_H

#include "InputMode.hpp"

namespace cms
{
	
	class MultithreadedServer : public InputMode
	{

	public:
		MultithreadedServer(int port);
		
		virtual void run(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);

	private:
		int port; // port that the server will listen on
		
	};

}

#endif