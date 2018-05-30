#include "doubles.h"

#include <chrono>
#include <iostream>
#include <thread>

int HTTPClient::Send(const std::string &request, std::string &data)
{
	// fake for the sake of the exercise
	std::cerr << "HTTP " << request << "..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	data = "data";
	return 200;
}

//////////////////////////////////////////////////////////////////////////

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
			// get task from que
			std::string res = que_.front();
			que_.pop_front();
			lock.unlock();

			// send request
			std::string data;
			int code = http_.Send("GET " + res, data);

			// execute callback
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
	std::unique_lock<std::mutex> lock(mtx_);
	succeeded_ = succeeded;
	failed_ = failed;
}
