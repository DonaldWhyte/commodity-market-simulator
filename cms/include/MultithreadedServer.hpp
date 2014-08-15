#ifndef CMS_MULTITHREADEDSERVER_H
#define CMS_MULTITHREADEDSERVER_H

#include "InputMode.hpp"
#include "ClientThreadManager.hpp"
#include <boost/asio.hpp>

namespace cms
{

	// TODO: comment
	static const bool THREAD_LOGGING_ENABLED = true;

	class MultithreadedServer : public InputMode
	{

	public:
		MultithreadedServer(int port);
		
		virtual void run(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);

	private:
		// TODO: comment
		void startAsynchronousAccept(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser);
		void stopAsynchronousAccept();
		void startAccept();
		void handleAccept(SocketPtr socket);

		typedef std::tr1::shared_ptr<boost::asio::io_service> IOServicePtr;
		typedef std::tr1::shared_ptr<boost::asio::ip::tcp::acceptor> AcceptorPtr;

		ClientThreadManagerPtr clientThreadManager;
		IOServicePtr ioService;
		AcceptorPtr acceptor;
	
		int port; // port that the server will listen on
		
	};

}

#endif