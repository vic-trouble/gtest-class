#include <gtest/gtest.h>

#include "doubles.h"

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(DownloadQueue, Succeeded_Callback_Should_Be_Called_When_Server_Returns_Success)
{
	// arrange
	bool succeededCalled = false;
	auto succeed = [&succeededCalled](const std::string &res) {succeededCalled = true; };
	
	DownloadQueue que;
	que.SetCallbacks(std::move(succeed), {});

	// act
	que.Add("res");
	que.Cancel();

	// assert
	EXPECT_TRUE(succeededCalled);
}

TEST(DownloadQueue, Failed_Callback_Should_Be_Called_When_Server_Returns_Error)
{
	// arrange
	bool failedCalled = false;
	auto failed = [&failedCalled](const std::string &res) {failedCalled = true; };

	DownloadQueue que;
	que.SetCallbacks({}, std::move(failed));

	// act
	que.Add("res");
	que.Cancel();

	// assert
	EXPECT_TRUE(failedCalled);
}
