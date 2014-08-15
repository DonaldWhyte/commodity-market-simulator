#include "TCPInputMode.hpp"
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
			acceptor.accept(*serverSocket);

			try
			{
				while (true)
				{
					char data[BUFFER_SIZE] = { 0 };
					boost::system::error_code error;
					size_t length = serverSocket->read_some(
						boost::asio::buffer(data), error);

					std::cout << data << std::endl;
					break;
				}
			}
			catch (std::exception& ex)
			{
				std::cout << "Exception occurred in server: " << ex.what() << std::endl;
			}

			/*
			boost::thread serverThread(
				boost::bind(session, serverSocket)
			);*/
		}

		std::cout << "TODO" << std::endl;
	}

}