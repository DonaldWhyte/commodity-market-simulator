#ifndef CMS_LOCK_H
#define CMS_LOCK_H

#include <boost/thread/mutex.hpp>

namespace cms
{

	/*
	 * CLASS: Lock<T>
	 * DESCRIPTION: Generic mutex lock class. It takes an instance
	 * of type T and keeps a copy of it.
	 *
	 * When the applications wishes to read/write this value, it
	 * acquires a pointer to it using acquire(), which LOCKS the
	 * value in the process (preventing other code from accessing it).
	 * When the application is done with the value, it must release
	 * the lock using release().
	 *
	 * New copies of the value can be retrieved using getCopy().
	 * This can be called without owning the lock on the value.
	*/
	template<typename T>
	class Lock
	{

	public:
		Lock(const T& instance) : instance(instance)
		{
		}

		/* Lock resource and retrieve pointer to it. */
		T* acquire()
		{
			lock.lock();
			return &instance;
		}

		void release()
		{
			lock.unlock();
		}

		/* Utility method. Returns a copy of the locked
		 * resource safely, by LOCKING, COPYING and then
		 * UNLOCKING. */
		T getCopy()
		{
			lock.lock();
			T copy = instance;
			lock.unlock();
			return copy;
		}

	private:
		boost::mutex lock;
		T instance;

	};

}

#endif