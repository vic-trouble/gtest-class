#include <gtest/gtest.h>

#include "leap.h"

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(IsLeap, True_When_Divisable_By_400)
{
	EXPECT_TRUE(isLeap(1600));
	EXPECT_TRUE(isLeap(2000));
}

TEST(IsLeap, False_When_Divisable_By_100_But_Not_By_400)
{
	EXPECT_FALSE(isLeap(1700));
	EXPECT_FALSE(isLeap(1800));
}

TEST(IsLeap, True_When_Divisable_By_4_But_Not_By_100)
{
	EXPECT_TRUE(isLeap(2008));
	EXPECT_TRUE(isLeap(2012));
}

TEST(IsLeap, False_When_Not_Divisable_By_4)
{
	EXPECT_FALSE(isLeap(2017));
	EXPECT_FALSE(isLeap(2018));
}