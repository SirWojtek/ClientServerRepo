#include <mutex>

#include "MessageQueue.hpp"
#include "NetworkMessage.hpp"

void MessageQueue::pushMessage(const std::string& message)
{
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(message);
	conditional_.notify_all();
}

std::string MessageQueue::popMessage()
{
	std::unique_lock<std::mutex> lock(mutex_);
	while (queue_.empty()) conditional_.wait(lock);

	std::string message = queue_.front();
	queue_.pop();
	return message;
}
