#ifndef MESSAGE_QUEUE_HPP_
#define MESSAGE_QUEUE_HPP_

#include <string>
#include <queue>
#include <memory>
#include <condition_variable>
#include <mutex>

#include "IMessageQueue.hpp"

class MessageQueue : public IMessageQueue
{
public:
    void pushMessage(const std::string& message);
    std::string popMessage();

private:
    std::queue<std::string> queue_;
    std::condition_variable conditional_;
    std::mutex mutex_;
};

#endif  // MESSAGE_QUEUE_HPP_
