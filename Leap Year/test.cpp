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
