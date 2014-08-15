#include "MultithreadedServer.hpp"
#include "CMSException.hpp"
#include "NetworkException.hpp"
#include "ServerCommon.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <tr1/memory>

using namespace boost::asio;

// NOTE: Code inspired from Blocking TCP Server example
// in Boost 1.52.0 documentation.

namespace cms
{

	void clientSession(SocketPtr socket, int threadNo,
		OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		try
		{
			while (true)
			{
				// Receive command from client
				char data[BUFFER_SIZE] = { 0 };
				boost::system::error_code error;
				socket->read_some(boost::asio::buffer(data), error);
				// If connection error with client, terminate the session
				// the server by breaking out of the loop
				if (error == error::eof) // connection cleanly closed
				{
					std::cout << "Client has closed connection" << std::endl;
					break;
				}
				else if (error)
				{
					std::stringstream errorMessage;
					errorMessage << "Connection error with client (error code " << error << ")";
					throw net::NetworkException(errorMessage.str());
				}
				// Parse command and execute it
				// If exception occurs in command parsing or execution,
				// then send exception message back to client
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

				socket->send(boost::asio::buffer(&result[0], result.size()));
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "EXCEPTION THROWN IN THREAD " << threadNo << ": " << ex.what() << std::endl;

		}
		std::cout << "TERMINATING THREAD " << threadNo << std::endl;
	}

	MultithreadedServer::MultithreadedServer(int port) : port(port), threadCounter(0)
	{
	}

	void MultithreadedServer::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		io_service ioService;
		ip::tcp::acceptor acceptor(ioService,
			ip::tcp::endpoint(ip::tcp::v4(), port));
		while (true)
		{
			// Wait until client requests a connection
			SocketPtr socketToClient(new ip::tcp::socket(ioService));
			acceptor.accept(*socketToClient);
			// Create a thread to handle the new client
			std::cout << "NEW CLIENT CONNECTED" << std::endl;
			std::cout << "STARTING THREAD " << threadCounter << std::endl;
			boost::thread clientSessionThread(boost::bind(
				clientSession, socketToClient, threadCounter,
				orderManager, commandParser));
			clientSessionThread.detach();

			threadCounter++;
		}

		// Client is connected! Serve the connected client
		// until it disconnects. Then, terminate the server
		
		std::cout << "TERMINATING SERVER" << std::endl;
	}

}