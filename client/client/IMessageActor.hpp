#pragma once

#include <memory>
#include <string>

class IMessageActor
{
public:
	virtual void asyncSend(std::shared_ptr<std::string> message) = 0;
	virtual bool asyncGet() = 0;
};