#include <gmock/gmock.h>

#include "doubles.h"

using testing::_;
using testing::Return;

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class MockHttpClient : public IHTTPClient
{
public:
	MOCK_METHOD2(Send, int(const std::string &request, std::string &response));
};

TEST(DownloadQueue, Succeeded_Callback_Should_Be_Called_When_Server_Returns_Success)
{
	// arrange
	bool succeededCalled = false;
	auto succeed = [&succeededCalled](const std::string &res) {succeededCalled = true; };
	
	MockHttpClient mock_http;
	ON_CALL(mock_http, Send(_, _)).WillByDefault(Return(200));

	DownloadQueue que(mock_http);
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

	MockHttpClient mock_http;
	ON_CALL(mock_http, Send(_, _)).WillByDefault(Return(501));

	DownloadQueue que(mock_http);
	que.SetCallbacks({}, std::move(failed));

	// act
	que.Add("res");
	que.Cancel();

	// assert
	EXPECT_TRUE(failedCalled);
}
