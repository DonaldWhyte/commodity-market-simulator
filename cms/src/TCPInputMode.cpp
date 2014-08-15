#include "TCPInputMode.hpp"
#include "CMSException.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <tr1/memory>

using namespace boost::asio;

typedef std::tr1::shared_ptr<ip::tcp::socket> SocketPtr;

static const unsigned int BUFFER_SIZE = 1024;

// NOTE: Code inspired from Blocking TCP Server example
// in Boost 1.52.0 documentation.

namespace cms
{

	TCPInputMode::TCPInputMode(int port) : port(port)
	{
	}

	void TCPInputMode::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		io_service ioService;
		ip::tcp::acceptor acceptor(ioService,
			ip::tcp::endpoint(ip::tcp::v4(), port));
		while (true)
		{
			SocketPtr serverSocket(new ip::tcp::socket(ioService));
			// Blocks until client sends a request
			acceptor.accept(*serverSocket);

			// Client has sent command! Parse it, execute it and
			// then close the connection with the client.
			try
			{
				// Receive command from client
				char data[BUFFER_SIZE] = { 0 };
				boost::system::error_code error;
				size_t length = serverSocket->read_some(
					boost::asio::buffer(data), error);
				std::cout << "RECEIVED COMMAND: " << data << std::endl;
				// Parse command and execute it
				// If exception occurs in command parsing or execution,
				// then send exception message back to client
				std::cout << "EXECUTING COMMAND..." << std::endl;
				std::string result;
				try
				{
					CommandPtr command = commandParser->parse(data);
				 	result = command->execute(orderManager);
				}
				catch (const CMSException& ex)
				{
					result = ex.what();
				}

				std::cout << "SENDING RESULT: " << result << std::endl;
				serverSocket->send(boost::asio::buffer(&result[0], result.size()));

				serverSocket->close();
			}
			catch (std::exception& ex)
			{
				std::cout << "Exception occurred in server: " << ex.what() << std::endl;
			}
		}
	}

}