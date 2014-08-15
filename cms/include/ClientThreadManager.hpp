#ifndef CMS_CLIENTTHREADMANAGER_H
#define CMS_CLIENTTHREADMANAGER_H

#include "OrderManager.hpp"
#include "CommandParser.hpp"
#include "ServerCommon.hpp"

namespace cms
{

	class ClientThreadManager
	{

	public:
		ClientThreadManager(OrderManagerPtr orderManager,
			std::tr1::shared_ptr<CommandParser> commandParser,
			bool logActivities);

		/* Start new thread that uses given socket to communicate with client.
		 * The number of the newly started thread is returned. */
		int start(SocketPtr clientSocket);
		/* Tell thread manager that a thread has stopped. */
		void threadStopped(int threadNo);

		/* True if thread activity logging has been enabled. */
		bool loggingEnabled() const;
		/* Enables/disables thread logging. */
		void setLogging(bool logActivities);

		int activeThreads() const;

	private:
		OrderManagerPtr orderManager;
		std::tr1::shared_ptr<CommandParser> commandParser;
		
		bool logActivities; // if true, activities of threads are logged
		int threadCounter; // used to assign threads numbers
		int numActiveThreads; // number of actively running threads remaining

	};

}

#endif