#pragma once

#include <memory>
#include <string>
#include <future>

#include "IMessageActor.hpp"
#include "Console.hpp"
#include "IMessageQueue.hpp"
#include "SharedVariable.hpp"

class MessageWriter : public IMessageActor
{
public:
	MessageWriter(std::shared_ptr<SharedVariable<IMessageQueue>> messageQueue) :
		console_("MessageWriter") {}

	void asyncSend(std::shared_ptr<std::string> message);
	bool asyncGet();

private:
	bool sendMessage(std::shared_ptr<std::string> message);

	std::shared_ptr<SharedVariable<IMessageQueue>> messageQueue_;
	std::shared_future<bool> writerThread_;
	Console console_;
};

