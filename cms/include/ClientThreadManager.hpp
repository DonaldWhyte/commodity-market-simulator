#ifndef CMS_CLIENTTHREADMANAGER_H
#define CMS_CLIENTTHREADMANAGER_H

#include "OrderManager.hpp"
#include "CommandParser.hpp"
#include "ServerCommon.hpp"
#include "Lock.hpp"
#include <boost/shared_ptr.hpp>

namespace cms
{

	/*
	 * CLASS: ClientThreadManager
	 * DESCRIPTION: Manages threads used to communicate with
	 * connected clients. start() spawns a new thread to deal
	 * with the given client socket, which returns the new
	 * thread's unique ID. When a client disconnects, the ID
	 * of that client's thread must be passed to threadStopped().
	*/
	class ClientThreadManager
	{

	public:
		ClientThreadManager(OrderManagerLockPtr orderManager,
			boost::shared_ptr<CommandParser> commandParser,
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

		/* Return number of threads currently active. */
		int activeThreads();

	private:
		void incrementThreadCounter();
		void incrementActiveThreads();
		void decrementActiveThreads();

		OrderManagerLockPtr orderManager;
		boost::shared_ptr<CommandParser> commandParser;

		bool logActivities; // if true, activities of threads are logged

		Lock<int> threadCounterLock; // used to assign threads numbers
		Lock<int> numActiveThreadsLock; // number of actively running threads remaining

	};

	typedef boost::shared_ptr<ClientThreadManager> ClientThreadManagerPtr;

}

#endif