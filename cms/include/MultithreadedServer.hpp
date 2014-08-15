#ifndef CMS_MULTITHREADEDSERVER_H
#define CMS_MULTITHREADEDSERVER_H

#include "InputMode.hpp"
#include "ClientThreadManager.hpp"
#include <boost/asio.hpp>

namespace cms
{

	// Set to true if the CMS server should log when
	// threads are created/destroyed 
	static const bool THREAD_LOGGING_ENABLED = true;

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