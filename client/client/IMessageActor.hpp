#pragma once

#include <memory>
#include <string>

class IMessageActor
{
public:
	virtual ~IMessageActor() {}
	virtual void asyncSend(std::shared_ptr<std::string> message) = 0;
	virtual bool asyncGet() = 0;
};
typedef std::shared_ptr<IMessageActor> MessageActorPtr;
