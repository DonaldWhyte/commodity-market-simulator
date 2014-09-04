#include <iostream>
#include <gtest/gtest.h>
#include "TestUtil.hpp"
#include "TestCommands.hpp"
#include "TestLock.hpp"
#include "TestOrderManager.hpp"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}