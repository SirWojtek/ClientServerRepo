#include <mutex>
#include <chrono>

#include "MessageQueue.hpp"

void MessageQueue::pushMessage(const std::string& message)
{
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push(message);
    conditional_.notify_all();
}

std::shared_ptr<std::string> MessageQueue::popMessage()
{
    std::unique_lock<std::mutex> lock(mutex_);
    std::cv_status status;

    if (queue_.empty())
    {
        status = conditional_.wait_for(lock, std::chrono::seconds(conditionalTimeout_));
    }

    if (status == std::cv_status::timeout)
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
