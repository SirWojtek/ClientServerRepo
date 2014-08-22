#pragma once

#include <string>
#include <queue>
#include <memory>

#include "IMessageQueue.hpp"

class MessageQueue : public IMessageQueue
{
public:
	void pushMessage(std::string&& message);
	std::shared_ptr<std::string> popMessage();
	bool isEmpty();

private:
	std::queue<std::string> queue_;
};

