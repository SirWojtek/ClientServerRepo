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
    conditional_.wait_for(lock, std::chrono::seconds(conditionalTimeout));

    if (queue_.empty())
    {
        return nullptr;
    }

    std::string message = queue_.front();
    queue_.pop();
    conditional_.notify_all();
    return std::make_shared<std::string>(message);
}

void MessageQueue::waitForEmptyQueue()
{
    std::unique_lock<std::mutex> lock(mutex_);
    while (!queue_.empty()) conditional_.wait(lock);
}
