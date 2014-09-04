#ifndef CMS_TEST_LOCK_H
#define CMS_TEST_LOCK_H

#include <gtest/gtest.h>
#include "Lock.hpp"

namespace cms
{

	namespace test
	{

		TEST(LockTest, AcquireRelease)
		{
			// Construct lock for integer
			Lock<int> testLock(5);
			ASSERT_EQ(5, testLock.getCopy());
			// Change value of locked integer
			int* val = testLock.acquire();
			*val = 6;
			testLock.release();
			// Ensure the changes were actually made
			ASSERT_EQ(6, testLock.getCopy());
		}

	}

}

#endif