#pragma once

#include <string>
#include <queue>
#include <memory>
#include <condition_variable>
#include <mutex>

#include "IMessageQueue.hpp"

class MessageQueue : public IMessageQueue
{
public:
	void pushMessage(std::string&& message);
	std::shared_ptr<std::string> popMessage();

private:
	std::queue<std::string> queue_;
	std::condition_variable conditional_;
	std::mutex mutex_;
};

