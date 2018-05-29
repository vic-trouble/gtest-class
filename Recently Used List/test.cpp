#include <gtest/gtest.h>

#include "recent.h"

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(RUList, Empty_When_Constructed)
{
	// arrange
	Recent::RUList rul;

	// assert
	EXPECT_EQ(rul.size(), 0);
}

TEST(RUList, Most_Recent_Item_Is_First)
{
	// arrange
	Recent::RUList rul;

	// act
	rul.push("old");
	rul.push("new");

	// assert
	ASSERT_EQ(rul.size(), 2);
	EXPECT_EQ(rul[0], "new");
	EXPECT_EQ(rul[1], "old");
}

TEST(RUList, Limited_Capacity)
{
	// arrange
	Recent::RUList rul(2);

	// act
	rul.push("drop");
	rul.push("old");
	rul.push("new");

	// assert
	ASSERT_EQ(rul.size(), 2);
	EXPECT_EQ(rul[0], "new");
	EXPECT_EQ(rul[1], "old");
}