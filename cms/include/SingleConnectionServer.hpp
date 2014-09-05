#ifndef CMS_SINGLECONNECTIONSERVER_H
#define CMS_SINGLECONNECTIONSERVER_H

#include "InputMode.hpp"

namespace cms
{
	
	/*
	 * CLASS: SingleConnectionServer
	 * DESCRIPTION: Accepts commands from a remote TCP socket.
	 *
	 * This input mode listens on a specified port until
	 * a client establishes a connection. Then, it receives
	 * commands, executes them and sends the results back
	 * to the client.

	 * Once the client disconnects, this input mode terminates.
	*/
	class SingleConnectionServer : public InputMode
	{

	public:
		SingleConnectionServer(int port);
		
		virtual void run(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser);

	private:
		// Port that the server will listen on
		int port;
		
	};

}

#endif