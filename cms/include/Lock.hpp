#ifndef CMS_LOCK_H
#define CMS_LOCK_H

#include <boost/thread/mutex.hpp>

namespace cms
{

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