#include "MultithreadedServer.hpp"
#include "ServerCommon.hpp"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

// NOTE: Code inspired from Blocking TCP Server example
// in Boost 1.52.0 documentation.

namespace cms
{

	/* Thread which continuously listens for new client
	 * connections. The thread terminates when all
	 * connected clients have disconnected. */
	void runListenerThread(int port,
		ClientThreadManagerPtr clientThreadManager,
		std::tr1::shared_ptr<bool> running)
	{
		io_service ioService;
		ip::tcp::acceptor acceptor(ioService,
			ip::tcp::endpoint(ip::tcp::v4(), port));
		ioService.run();

		while (running)
		{
			SocketPtr clientSocket(new ip::tcp::socket(ioService));
			acceptor.accept(*clientSocket);
			clientThreadManager->start(clientSocket);
		}

		acceptor.cancel();
		ioService.stop();
	}

	MultithreadedServer::MultithreadedServer(int port) : port(port)
	{
	}

	void MultithreadedServer::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		// Construct object which handles creation of client
		// threads and keeps track of their 
		ClientThreadManagerPtr clientThreadManager(
			new ClientThreadManager(orderManager, commandParser,
				THREAD_LOGGING_ENABLED));

		// Fire off thread to listen for new client connections
		// This new thread handles accepting connections, while
		// the current (main) thread monitors how many active
		// connections there are (terminating server where 
		// all clients have disconnected)
		std::tr1::shared_ptr<bool> running(new bool(true));
		boost::thread listenerThread(boost::bind(
			&runListenerThread, port, clientThreadManager, running));
		listenerThread.detach();

		// Remain idle until the first client has connected
		std::cout << "WAITING FOR CLIENT TO CONNECT..." << std::endl;
		while (clientThreadManager->activeThreads() == 0)
		{
		}
		// Wait until all clients have disconnected
		while (clientThreadManager->activeThreads() > 0)
		{
		}

		// Terminate listener thread by deactivating running flag
		*running = false;
		
		std::cout << "TERMINATING SERVER" << std::endl;
	}

}