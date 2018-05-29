#pragma once

#include <list>
#include <mutex>
#include <string>

struct IHTTPClient
{
	virtual ~IHTTPClient() = default;

	virtual int Send(const std::string &request, std::string &response) = 0;
};

class HTTPClient: public IHTTPClient
{
public:
	int Send(const std::string &request, std::string &response) override;
};

using Callback = std::function<void(const std::string &resource)>;

class DownloadQueue
{
public:
	explicit DownloadQueue(IHTTPClient &http);
	~DownloadQueue();

	void Add(const std::string &resource);
	void Cancel();
	void SetCallbacks(Callback &&succeeded, Callback &&failed);

private:
	void WorkerProc();

private:
	IHTTPClient &http_;
	std::list<std::string> que_;
	std::thread worker_;
	std::mutex mtx_;
	bool stopFlag_ = false;
	Callback succeeded_, failed_;
};
