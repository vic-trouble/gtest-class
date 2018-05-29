#include "doubles.h"

#include <chrono>
#include <thread>

int HTTPClient::Send(const std::string &request, std::string &response)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	// simplified for the sake of the exercise
	response = "here's your data";
	return 200;
}

DownloadQueue::DownloadQueue()
{
	worker_ = std::thread([](DownloadQueue *self) { self->WorkerProc(); }, this);
}

void DownloadQueue::Add(const std::string &resource)
{
	std::lock_guard<std::mutex> lock(mtx_);
	que_.push_back(resource);
}

void DownloadQueue::WorkerProc()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(mtx_);
		if (!que_.empty())
		{
			std::string res = que_.front();
			que_.pop_front();
			lock.unlock();
			std::string data;
			int code = http_.Send("GET " + res, data);
			if (200 <= code && code < 300)
			{
				if (succeeded_)
					succeeded_(res);
			}
			else
			{
				if (failed_)
					failed_(res);
			}
			continue;
		}

		if (stopFlag_)
			break;

		lock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void DownloadQueue::Cancel()
{
	{
		std::unique_lock<std::mutex> lock(mtx_);
		stopFlag_ = true;
	}
	if (worker_.joinable())
		worker_.join();
}

DownloadQueue::~DownloadQueue()
{
	Cancel();
}

void DownloadQueue::SetCallbacks(Callback &&succeeded, Callback &&failed)
{
	succeeded_ = succeeded;
	failed_ = failed;
}
