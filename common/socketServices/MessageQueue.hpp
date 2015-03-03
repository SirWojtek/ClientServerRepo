#ifndef MESSAGE_QUEUE_HPP_
#define MESSAGE_QUEUE_HPP_

#include <string>
#include <queue>
#include <memory>
#include <condition_variable>
#include <mutex>

#include "IMessageQueue.hpp"
#include "common/utilities/Console.hpp"

class MessageQueue : public IMessageQueue
{
public:
    MessageQueue();

    void pushMessage(const std::string& message);
    std::shared_ptr<std::string> popMessage();
    void waitForEmptyQueue();

private:
    std::queue<std::string> queue_;
    std::condition_variable conditional_;
    std::mutex mutex_;

    const unsigned conditionalTimeout_ = 2;
    Console console_;
};

#endif  // MESSAGE_QUEUE_HPP_
