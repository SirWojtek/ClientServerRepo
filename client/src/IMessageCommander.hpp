#ifndef IMESSAGE_COMMANDER_HPP_
#define IMESSAGE_COMMANDER_HPP_

#include <memory>
#include <thread>
#include <atomic>

#include "ITcpSocket.hpp"

typedef std::shared_ptr<std::thread> ThreadPtr;
class IMessageCommander
{
public:
    IMessageCommander() : stop_(false) {}

    virtual ThreadPtr start() = 0;

    void stop()
    {
        stop_.exchange(true);
    }
protected:
    std::atomic<bool> stop_;
};
typedef std::shared_ptr<IMessageCommander> MessageCommanderPtr;

#endif  // IMESSAGE_COMMANDER_HPP_
