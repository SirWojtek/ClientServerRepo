#include <thread>
#include <stdexcept>

#include "server/src/ServerSession.hpp"
#include "common/messages/MessageUtilities.hpp"

using common::messagetype::MessageType;
using boost::asio::ip::tcp;

std::shared_ptr<std::thread> ServerSession::start()
{
    return std::make_shared<std::thread>(&ServerSession::startThreadsAndRun,
        this, shared_from_this());
}

void ServerSession::startThreadsAndRun(std::shared_ptr<IServerSession> self)
{
    readerWrapper_->createReaderForQueue(wrapper_, socketNumber_);
    writerWrapper_->createWriterForQueue(wrapper_, socketNumber_);

    readerThread_ = readerWrapper_->startCommander();
    writerThread_ = writerWrapper_->startCommander();

    console_.info << "Service started";
    runSession();
}

void ServerSession::runSession()
{
    int messageIndex;
    if (!wasClientLoggedInCorrectly())
    {
        tearDown();
        console_.info << "Client was not logged in correctly, exiting.";
        return;
    }
    messageIndex = getMessage();
    sendPlayerPosition(0, 0, 0);
    while(true)
    {
        messageIndex = getMessage();
        writerWrapper_->waitForEmptyQueueWithTimeout();
        if (messageIndex != noMessage_)
        {
            if (receivedMessages_[messageIndex].first != MessageType::Logout)
            {
                sendOkResponse(true);
            }
            else
            {
                stop();
            }
        }
        if (stop_.load())
        {
            break;
        }
    }
    tearDown();
    printMessageCounter();
    console_.info << "Server session stopped.";
}

void ServerSession::tearDown()
{
    if (readerThread_ && readerThread_->joinable())
    {
        readerWrapper_->stopCommander();
        readerThread_->join();
        console_.info << "Reader thread joined";
    }

    if (writerThread_ && writerThread_->joinable())
    {
        writerWrapper_->waitForEmptyQueue();
        writerWrapper_->stopCommander();
        writerThread_->join();
        console_.info << "Writer thread joined";
    }
    console_.info << "Service ended";
}

void ServerSession::stop()
{
    stop_.exchange(true);
}

bool ServerSession::wasClientLoggedInCorrectly()
{
    int messageIndex = getMessage();
    if (messageIndex != noMessage_)
    {
        if (receivedMessages_[messageIndex].first == MessageType::Login)
        {
            sendOkResponse(true);
            return true;
        }
    }
    return false;
}

int ServerSession::getMessage()
{
    std::shared_ptr<std::string> messageString;
    if (messageString = readerWrapper_->popMessage())
    {
        timeBetweenMessageReceiveAndSend_ = high_resolution_clock::now();
        MessageType receivedMessageType = common::getMessageType(*messageString);
        std::size_t foundSemiColon = messageString->find(";");
        messageString = std::make_shared<std::string>(
            messageString->substr(0, foundSemiColon)); // remove needless semi-colon at the end
        
        cyclicPushReceivedMessages(receivedMessageType, messageString);
        return (receivedMessages_.size()-1); // index of just inserted value
    }
    return noMessage_;
}

void ServerSession::cyclicPushReceivedMessages(MessageType receivedMessageType,
    std::shared_ptr<std::string> messageString)
{
    if (receivedMessages_.size() < 100)
    {
        receivedMessages_.push_back(messagePair(receivedMessageType, messageString));
    }
    else
    {
        std::rotate(receivedMessages_.begin(), receivedMessages_.begin()+1,
            receivedMessages_.end());
        receivedMessages_.erase(receivedMessages_.end()-1);
        receivedMessages_.push_back(messagePair(receivedMessageType, messageString));
    }
    messageCounter_[receivedMessageType]++;
    console_.debug << "Amount of received messages: " + std::to_string(receivedMessages_.size());
}

void ServerSession::sendOkResponse(bool serwerAllows)
{
    common::OkResponse okMessage;
    okMessage.serverAllows = serwerAllows;
    std::string json = common::getMessageJson<common::OkResponse>(okMessage);
    totalTimeBetweenMessageReceiveAndSend_ += duration_cast<duration<double>>(high_resolution_clock::now() - timeBetweenMessageReceiveAndSend_);
    amountOfMessagesSent_++;
    writerWrapper_->pushMessage(json);
    console_.debug << "OkMessage added to queue";
}

void ServerSession::printMessageCounter()
{
    double totalTicks = float(totalTimeBetweenMessageReceiveAndSend_.count()/amountOfMessagesSent_);
    console_.info << "____________________";
    console_.info << "Message Counter:";
    console_.info << "Incorrect:             " + std::to_string(messageCounter_[common::messagetype::Incorrect]);
    console_.info << "UpdateEnvironment:     " + std::to_string(messageCounter_[common::messagetype::UpdateEnvironment]);
    console_.info << "UpdatePlayer:          " + std::to_string(messageCounter_[common::messagetype::UpdatePlayer]);
    console_.info << "OkResponse:            " + std::to_string(messageCounter_[common::messagetype::OkResponse]);
    console_.info << "Login:                 " + std::to_string(messageCounter_[common::messagetype::Login]);
    console_.info << "CurrentPlayerPosition: " + std::to_string(messageCounter_[common::messagetype::CurrentPlayerPosition]);
    console_.info << "Logout:                " + std::to_string(messageCounter_[common::messagetype::Logout]);
    console_.info << "Total amount of messages sent: " + std::to_string(amountOfMessagesSent_);
    console_.info << "Mean time between message receive and message send [sec] : " + std::to_string(totalTicks);
    console_.info << "____________________";
    std::ofstream outputFile("serverLogs/"+std::to_string(socketNumber_)+".log");
    outputFile << totalTicks << "\n" << updateEnvironmentCounter_ << "\n" << messageCounter_[common::messagetype::UpdatePlayer];
}

messageCounter ServerSession::getMessageCounter()
{
    return messageCounter_;
}
messagePairVec ServerSession::getMessagePairVector()
{
    return receivedMessages_;
}

bool ServerSession::loginService()
{
    return false;
}
bool ServerSession::updatePlayerPositionByJson(std::string json)
{
    return false;
}

void ServerSession::sendOtherPlayersUpdate()
{
    
}

void ServerSession::sendPlayerPosition(int x, int y, int z)
{
    common::CurrentPlayerPosition position;
    position.position = std::make_tuple(x, y, z);
    std::string json = common::getMessageJson<common::CurrentPlayerPosition>(position);
    totalTimeBetweenMessageReceiveAndSend_ += duration_cast<duration<double>>(high_resolution_clock::now() - timeBetweenMessageReceiveAndSend_);
    amountOfMessagesSent_++;
    writerWrapper_->pushMessage(json);
    console_.debug << "CurrentPlayerPosition added to queue: " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " ";
}