#include <gtest/gtest.h>

#include "greet.h"

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Greet, Should_Be_Hello_Name_When_Single_Name)
{
	EXPECT_EQ(greet("Bob"), "Hello, Bob.");
}
