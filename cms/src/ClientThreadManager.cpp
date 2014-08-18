#include "ClientThreadManager.hpp"
#include "CMSException.hpp"
#include "NetworkException.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using namespace boost::asio;

namespace cms
{

	void clientSession(SocketPtr socket, int threadNo,
		ClientThreadManager* threadManager,
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
		
		// Inform thread manager that this thread is no longer running
		threadManager->threadStopped(threadNo);
	}

	ClientThreadManager::ClientThreadManager(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser, bool logActivities)
		: orderManager(orderManager), commandParser(commandParser),
		logActivities(logActivities),
		threadCounterLock(0), numActiveThreadsLock(0)
	{
	}

	int ClientThreadManager::start(SocketPtr socket)
	{
		int threadCounter = threadCounterLock.getCopy();

		if (logActivities)
		{
			std::cout << "NEW CLIENT CONNECTED" << std::endl;
			std::cout << "STARTING THREAD " << threadCounter << std::endl;
		}

		int threadNo = threadCounter;
		boost::thread clientSessionThread(boost::bind(
			clientSession, socket, threadNo,
			this, orderManager, commandParser));
		clientSessionThread.detach();

		incrementThreadCounter();
		incrementActiveThreads();

		return threadNo;
	}

	void ClientThreadManager::threadStopped(int threadNo)
	{
		if (logActivities)
		{
			std::cout << "THREAD " << threadNo << " STOPPED" << std::endl;
		}

		decrementActiveThreads();
	}

	bool ClientThreadManager::loggingEnabled() const
	{
		return logActivities;
	}

	void ClientThreadManager::setLogging(bool logActivities)
	{
		this->logActivities = logActivities;
	}

	int ClientThreadManager::activeThreads()
	{
		return numActiveThreadsLock.getCopy();
	}

	void ClientThreadManager::incrementThreadCounter()
	{
		int* threadCounter = threadCounterLock.acquire();
		(*threadCounter)++;
		threadCounterLock.release();
	}

	void ClientThreadManager::incrementActiveThreads()
	{
		int* numActiveThreads = numActiveThreadsLock.acquire();
		(*numActiveThreads)++;
		numActiveThreadsLock.release();
	}

	void ClientThreadManager::decrementActiveThreads()
	{
		int* numActiveThreads = numActiveThreadsLock.acquire();
		(*numActiveThreads)--;
		numActiveThreadsLock.release();
	}


}