#include <mutex>

#include "MessageQueue.hpp"

void MessageQueue::pushMessage(std::string&& message)
{
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(message);
	conditional_.notify_all();
}

std::shared_ptr<std::string> MessageQueue::popMessage()
{
	std::unique_lock<std::mutex> lock(mutex_);
	while (queue_.empty()) conditional_.wait(lock);

	std::shared_ptr<std::string> message = std::make_shared<std::string>(queue_.front());
	queue_.pop();
	return message;
}
