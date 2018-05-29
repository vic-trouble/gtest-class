#pragma once

#include <list>
#include <mutex>
#include <string>

class HTTPClient
{
public:
	int Send(const std::string &request, std::string &response);
};

using Callback = std::function<void(const std::string &resource)>;

class DownloadQueue
{
public:
	DownloadQueue();
	~DownloadQueue();

	void Add(const std::string &resource);
	void Cancel();
	void SetCallbacks(Callback &&succeeded, Callback &&failed);

private:
	void WorkerProc();

private:
	HTTPClient http_;
	std::list<std::string> que_;
	std::thread worker_;
	std::mutex mtx_;
	bool stopFlag_ = false;
	Callback succeeded_, failed_;
};
