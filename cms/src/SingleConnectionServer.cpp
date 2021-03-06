#include "SingleConnectionServer.hpp"
#include "CMSException.hpp"
#include "ServerCommon.hpp"
#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace boost::asio;

// NOTE: Code inspired from Blocking TCP Server example
// in Boost 1.52.0 documentation.

namespace cms
{

	SingleConnectionServer::SingleConnectionServer(int port) : port(port)
	{
	}

	void SingleConnectionServer::run(OrderManagerLockPtr orderManager,
		boost::shared_ptr<CommandParser> commandParser)
	{
		io_service ioService;
		ip::tcp::acceptor acceptor(ioService,
			ip::tcp::endpoint(ip::tcp::v4(), port));

		SocketPtr socketToClient(new ip::tcp::socket(ioService));
		// Blocks until client sends a request
		acceptor.accept(*socketToClient);
		// Client is connected! Serve the connected client
		// until it disconnects. Then, terminate the server
		while (true)
		{
			try
			{
				// Receive command from client
				char data[BUFFER_SIZE] = { 0 };
				boost::system::error_code error;
				socketToClient->read_some(boost::asio::buffer(data), error);
				// If connection error with client, terminate the session
				// the server by breaking out of the loop
				if (error == error::eof) // connection cleanly closed
				{
					std::cout << "Client has closed connection" << std::endl;
					break;
				}
				else if (error)
				{
					std::cout << "Connection error with client (error code " << error << ")" << std::endl;
					break;
				}
				std::cout << "RECEIVED COMMAND: " << data << std::endl;
				// Parse command and execute it
				// If exception occurs in command parsing or execution,
				// then send exception message back to client
				std::cout << "EXECUTING COMMAND..." << std::endl;
				std::string result;
				try
				{
					CommandPtr command = commandParser->parse(data);
				 	result = command->run(orderManager);
				}
				catch (const CMSException& ex)
				{
					result = ex.what();
				}

				std::cout << "SENDING RESULT: " << result << std::endl;
				socketToClient->send(boost::asio::buffer(&result[0], result.size()));
			}
			catch (std::exception& ex)
			{
				std::cout << "Exception occurred in server: " << ex.what() << std::endl;
			}
		}
		std::cout << "TERMINATING SERVER" << std::endl;
	}

}