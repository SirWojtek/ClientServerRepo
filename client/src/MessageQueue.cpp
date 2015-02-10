#include <mutex>
#include <chrono>

#include "MessageQueue.hpp"
#include "NetworkMessage.hpp"

void MessageQueue::pushMessage(const std::string& message)
{
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push(message);
	conditional_.notify_all();
}

std::shared_ptr<std::string> MessageQueue::popMessage()
{
	std::unique_lock<std::mutex> lock(mutex_);
	std::cv_status status = conditional_.wait_for(lock, std::chrono::seconds(1));

	if (status == std::cv_status::timeout)
	{
		return nullptr;
	}

	std::string message = queue_.front();
	queue_.pop();
	return std::make_shared<std::string>(message);
}
