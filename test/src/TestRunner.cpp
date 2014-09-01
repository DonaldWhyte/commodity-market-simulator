#include <iostream>
#include <gtest/gtest.h>

TEST(DummyTest, Dummy)
{
	ASSERT_EQ(3, 3);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}