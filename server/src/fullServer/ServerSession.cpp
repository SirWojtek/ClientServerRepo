#include <thread>
#include <stdexcept>

#include "server/src/ServerSession.hpp"
#include "common/messages/MessageUtilities.hpp"

using namespace common;
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
    if (!loginService())
    {
        tearDown();
        console_.info << "Client was not logged in correctly, exiting.";
        return;
    }
    while(true)
    {
        messageIndex = getMessage();
        writerWrapper_->waitForEmptyQueueWithTimeout();
        if (messageIndex != noMessage_)
        {
            switch(receivedMessages_[messageIndex].first)
            {
                case MessageType::UpdatePlayer:
                    if (updatePlayerPositionByJson(*receivedMessages_[messageIndex].second))
                    {
                        sendOkResponse(true);
                    }
                    else
                    {
                        sendOkResponse(false);
                    }
                    break;
                case MessageType::Logout:
                    stop();
                    break;
                default:
                    sendOkResponse(true);
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
            auto loginMessage = common::getMessage<common::Login>(
                *receivedMessages_[messageIndex].second);
            if (loginMessage == nullptr)
            {
                console_.error << "Something went wrong with deserializing: " + *receivedMessages_[messageIndex].second;
                sendOkResponse(false);
                return false;
            }
            Users loginData = databaseConnector_->getUsersBy(
                UserTypes::LOGIN, loginMessage->playerName);
            if (loginData.size() == 1)
            {
                userForSession_ = loginData[0];
                console_.info << "Login OK for user: " + loginMessage->playerName;
                sendOkResponse(true);
                return true;
            }
        }
    }
    sendOkResponse(false);
    return false;
}

bool ServerSession::loginService()
{
    if (!wasClientLoggedInCorrectly())
    {
        return false;
    }
    int messageIndex = getMessage();
    if (userForSession_.get<LOGIN_ID>() != "") // emptiness of Login implies emptiness of tuple
    {
        userForSession_.get<ISONLINE_ID>() = true;
        sendPlayerPosition(userForSession_.get<XPOS_ID>(),
            userForSession_.get<YPOS_ID>(), userForSession_.get<ZPOS_ID>());
        return (databaseConnector_->updateUser(userForSession_));
    }
    console_.error << "userForSession object is null";
    return false;
}

int ServerSession::getMessage()
{
    std::shared_ptr<std::string> messageString;
    if (messageString = readerWrapper_->popMessage())
    {
        timeBetweenMessageReceiveAndSend_ = clock();
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
    //console_.debug << "Amount of received messages: " + std::to_string(receivedMessages_.size());
}

void ServerSession::sendOkResponse(bool serwerAllows)
{
    common::OkResponse okMessage;
    okMessage.serverAllows = serwerAllows;
    std::string json = common::getMessageJson<common::OkResponse>(okMessage);
    totalTimeBetweenMessageReceiveAndSend_ += clock() - timeBetweenMessageReceiveAndSend_;
    amountOfMessagesSent_++;
    writerWrapper_->pushMessage(json);
    console_.debug << "OkMessage added to queue";
}

void ServerSession::sendPlayerPosition(int x, int y, int z)
{
    common::CurrentPlayerPosition position;
    position.position = std::make_tuple(x, y, z);
    std::string json = common::getMessageJson<common::CurrentPlayerPosition>(position);
    writerWrapper_->pushMessage(json);
    console_.debug << "CurrentPlayerPosition added to queue: " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " ";
}

bool ServerSession::updatePlayerPositionByJson(std::string json)
{
    auto message = common::getMessage<common::UpdatePlayer>(json);
    userForSession_.get<XPOS_ID>() += message->delta.first;
    userForSession_.get<YPOS_ID>() += message->delta.second;
    return (databaseConnector_->updateUser(userForSession_));
}

void ServerSession::printMessageCounter()
{
    double totalTicks = float(totalTimeBetweenMessageReceiveAndSend_/amountOfMessagesSent_);
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
    console_.info << "Mean time between message receive and message send [ms] : " + std::to_string(totalTicks/float(CLOCKS_PER_SEC));
    console_.info << "____________________";
}

messageCounter ServerSession::getMessageCounter()
{
    return messageCounter_;
}
messagePairVec ServerSession::getMessagePairVector()
{
    return receivedMessages_;
}
