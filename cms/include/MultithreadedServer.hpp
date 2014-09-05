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

	/*
	 * CLASS: MultithreadedServer
	 * DESCRIPTION: Accepts commands from remote TCP sockets.
	 *
	 * This input mode listens on a specified port for client
	 * connections. Once a client connects, a new thread is
	 * spawned to handle commands given by that client.
	 *
	 * Once all connected clients have disconnected, and there
	 * are no more client threads remaining, this input mode
	 * terminates.
	*/
	class MultithreadedServer : public InputMode
	{

	public:
		MultithreadedServer(int port);
		
		virtual void run(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser);

	private:
		int port; // port that the server will listen on
		
	};

}

#endif