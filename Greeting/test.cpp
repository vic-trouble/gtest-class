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

TEST(Greet, Should_Be_Hello_My_Friend_When_Name_Omitted)
{
	EXPECT_EQ(greet(""), "Hello, my friend.");
}

TEST(Greet, Should_Be_All_Caps_When_Name_In_Uppercase)
{
	EXPECT_EQ(greet("JERRY"), "HELLO JERRY!");
}

TEST(Greet, Should_Be_First_And_Second_When_Two_Names)
{
	EXPECT_EQ(greet("Alice, Bob"), "Hello, Alice and Bob.");
}

TEST(Greet, Should_Be_First_Comma_Second_And_Third_When_Three_Names)
{
	EXPECT_EQ(greet("Alice, Bob, Charlotte"), "Hello, Alice, Bob and Charlotte.");
}

TEST(Greet, Should_Shout_All_Caps_After_Normal_Greet_When_Mixed_Case_Names)
{
	EXPECT_EQ(greet("Amy, BRIAN, Charlotte"), "Hello, Amy and Charlotte. AND HELLO BRIAN!");
}