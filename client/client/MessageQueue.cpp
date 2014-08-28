#include <mutex>

#include "MessageQueue.hpp"
#include "NetworkMessage.hpp"

void MessageQueue::pushMessage(NetworkMessage&& message)
{
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(message);
	conditional_.notify_all();
}

void MessageQueue::pushMessage(const NetworkMessage& message)
{
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(NetworkMessage(message));
	conditional_.notify_all();
}

NetworkMessagePtr MessageQueue::popMessage()
{
	std::unique_lock<std::mutex> lock(mutex_);
	while (queue_.empty()) conditional_.wait(lock);

	NetworkMessagePtr message = std::make_shared<NetworkMessage>(queue_.front());
	queue_.pop();
	return message;
}
