#include "MessageQueue.hpp"

void MessageQueue::pushMessage(std::string&& message)
{
	queue_.push(message);
}

std::shared_ptr<std::string> MessageQueue::popMessage()
{
	std::shared_ptr<std::string> message = std::make_shared<std::string>(queue_.front());
	queue_.pop();
	return message;
}

bool MessageQueue::isEmpty()
{
	return queue_.empty();
}
