#ifndef CMS_TEST_UTIL
#define CMS_TEST_UTIL

#include <gtest/gtest.h>
#include "Util.hpp"
#include "CMSException.hpp"

namespace cms
{

	namespace test
	{

		TEST(UtilTest, ToInt)
		{
			// Test empty string
			EXPECT_THROW(util::toInt(""), CMSException);
			// Test non-integer value
			EXPECT_THROW(util::toInt("haha"), CMSException);
			// Test string that STARTS with an integer, but has non-digits
			EXPECT_THROW(util::toInt("12fdjhgydsj"), CMSException);
			// Test negative integer
			EXPECT_EQ(-12, util::toInt("-12"));
			// Test zero
			EXPECT_EQ(0, util::toInt("0"));
			// Test positive integer
			EXPECT_EQ(12, util::toInt("12"));
		}

		TEST(UtilTest, ToPositiveInt)
		{
			// Test empty string
			EXPECT_THROW(util::toPositiveInt(""), CMSException);
			// Test non-integer value
			EXPECT_THROW(util::toPositiveInt("haha"), CMSException);
			// Test string that STARTS with an integer, but has non-digits
			EXPECT_THROW(util::toPositiveInt("12fdjhgydsj"), CMSException);
			// Test negative integer
			EXPECT_THROW(util::toPositiveInt("-12"), CMSException);
			// Test zero
			EXPECT_THROW(util::toPositiveInt("0"), CMSException);
			// Test positive integer
			EXPECT_EQ(12, util::toPositiveInt("12"));
		}

		TEST(UtilTest, ToDouble)
		{
			// Test empty string
			EXPECT_THROW(util::toDouble(""), CMSException);
			// Test non-integer value
			EXPECT_THROW(util::toDouble("haha"), CMSException);
			// Test string that STARTS with an integer, but has non-digits
			EXPECT_THROW(util::toDouble("12fdjhgydsj"), CMSException);
			// Test negative integer
			EXPECT_EQ(-12.0, util::toDouble("-12"));
			// Test zero
			EXPECT_EQ(0.0, util::toDouble("0"));
			// Test positive integer
			EXPECT_EQ(12.0, util::toDouble("12"));

			// Test with decimal places
			EXPECT_THROW(util::toDouble("12.5724.sfdjhgydsj"), CMSException);
			EXPECT_EQ(-12.5724, util::toDouble("-12.5724"));
			EXPECT_EQ(0.5724, util::toDouble("0.5724"));
			EXPECT_EQ(12.5724, util::toDouble("12.5724"));
		}

		TEST(UtilTest, FromInt)
		{
			EXPECT_EQ("-12", util::fromInt(-12));
			EXPECT_EQ("0", util::fromInt(0));
			EXPECT_EQ("12", util::fromInt(12));
		}

		TEST(UtilTest, FromDouble)
		{
			EXPECT_EQ("-12", util::fromDouble(-12.0));
			EXPECT_EQ("0", util::fromDouble(0.0));
			EXPECT_EQ("12", util::fromDouble(12.0));
			EXPECT_EQ("-12.5724", util::fromDouble(-12.5724));
			EXPECT_EQ("0.5724", util::fromDouble(0.5724));
			EXPECT_EQ("12.5724", util::fromDouble(12.5724));
		}

	}

}

#endif