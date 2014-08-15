#include "MultithreadedServer.hpp"
#include "ServerCommon.hpp"
#include <boost/bind.hpp>

using namespace boost::asio;

// NOTE: Code inspired from Blocking TCP Server example
// in Boost 1.52.0 documentation.

namespace cms
{

	MultithreadedServer::MultithreadedServer(int port) : port(port)
	{
	}

	void MultithreadedServer::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		startAsynchronousAccept(orderManager, commandParser);		

		std::cout << "WAITING FOR CLIENT TO CONNECT..." << std::endl;
		while (clientThreadManager->activeThreads() == 0) // wait for at least once client
		{
		}
		while (clientThreadManager->activeThreads() > 0) // now wait until there are no connections
		{
		}

		// Stop listening for client requests
		stopAsynchronousAccept();
		
		std::cout << "TERMINATING SERVER" << std::endl;
	}

	void MultithreadedServer::startAsynchronousAccept(
		OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		clientThreadManager = ClientThreadManagerPtr(
			new ClientThreadManager(orderManager, commandParser, THREAD_LOGGING_ENABLED)
		);

		ioService = IOServicePtr(new io_service());
		acceptor = AcceptorPtr(new ip::tcp::acceptor(
			*ioService, ip::tcp::endpoint(ip::tcp::v4(), port)));

		startAccept();
	}

	void MultithreadedServer::stopAsynchronousAccept()
	{
		acceptor->cancel();
		ioService = IOServicePtr();
		clientThreadManager = ClientThreadManagerPtr();
	}

	void MultithreadedServer::startAccept()
	{
		SocketPtr clientSocket(new ip::tcp::socket(*ioService));
		acceptor->async_accept(*clientSocket,
			boost::bind(&MultithreadedServer::handleAccept, this, clientSocket)
		);
		ioService->run_one(); // ensure event processing loop is running
	}

	void MultithreadedServer::handleAccept(SocketPtr clientSocket)
	{
		clientThreadManager->start(clientSocket);
		startAccept();
	}

}