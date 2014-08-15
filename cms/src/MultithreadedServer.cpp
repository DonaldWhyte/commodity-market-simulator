#include "MultithreadedServer.hpp"
#include "ClientThreadManager.hpp"
#include "ServerCommon.hpp"
#include <boost/asio.hpp>

using namespace boost::asio;

// NOTE: Code inspired from Blocking TCP Server example
// in Boost 1.52.0 documentation.

namespace cms
{

	MultithreadedServer::MultithreadedServer(int port) : port(port), threadCounter(0)
	{
	}

	void MultithreadedServer::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		std::cout << "WAITING FOR CLIENT TO CONNECT..." << std::endl;

		io_service ioService;
		ip::tcp::acceptor acceptor(ioService,
			ip::tcp::endpoint(ip::tcp::v4(), port));
		ClientThreadManager clientThreadManager(
			orderManager, commandParser, true);

		do
		{
			// Wait until client requests a connection
			SocketPtr socketToClient(new ip::tcp::socket(ioService));
			acceptor.accept(*socketToClient);
			// Create a thread to handle the new client
			std::cout << "NEW CLIENT CONNECTED" << std::endl;
			clientThreadManager.start(socketToClient);
		} while (clientThreadManager.activeThreads() > 0);
		
		std::cout << "TERMINATING SERVER" << std::endl;
	}

}