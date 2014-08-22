#pragma once

#include <string>
#include <memory>

class IMessageQueue
{
public:
	virtual void pushMessage(std::string&& message) = 0;
	virtual std::shared_ptr<std::string> popMessage() = 0;
	virtual bool isEmpty() = 0;
};