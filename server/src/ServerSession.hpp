#ifndef SERVER_SESSION_HPP_
#define SERVER_SESSION_HPP_

#include "IServerSession.hpp"

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <atomic>
#include <thread>

#include "common/utilities/Console.hpp"
#include "common/messages/MessageUtilities.hpp"
#include "IBoostWrapper.hpp"
#include "ISocketServicesWrapper.hpp"

using boost::asio::ip::tcp;
using messagePair = std::pair<common::messagetype::MessageType, std::shared_ptr<std::string> >;
using messagePairVec = std::vector<messagePair>;
using messageCounter = std::map<common::messagetype::MessageType, unsigned>;

class ServerSession : public std::enable_shared_from_this<ServerSession>, public IServerSession
{
public:
  ServerSession(std::shared_ptr<IBoostWrapper> wrapper, SocketServicePtr readerWrapper,
    SocketServicePtr writerWrapper, int socketNumber):
    wrapper_(wrapper),
    socketNumber_(socketNumber),
    readerWrapper_(readerWrapper),
    writerWrapper_(writerWrapper),
    console_("ServerSession")
  {
    messageCounter_[common::messagetype::Incorrect] = 0;
    messageCounter_[common::messagetype::UpdateEnvironment] = 0;
    messageCounter_[common::messagetype::UpdatePlayer] = 0;
    messageCounter_[common::messagetype::OkResponse] = 0;
    messageCounter_[common::messagetype::Login] = 0;
    messageCounter_[common::messagetype::CurrentPlayerPosition] = 0;
    messageCounter_[common::messagetype::Logout] = 0;
  }

  std::shared_ptr<std::thread> start();
  void startThreadsAndRun(std::shared_ptr<IServerSession> self);
  void stop();
  void tearDown();
  bool wasClientLoggedInCorrectly();

private:
  void runSession();
  int getMessage();
  void sendOkResponse(bool serverAllows);
  void cyclicPushReceivedMessages(common::messagetype::MessageType receivedMessageType,
    std::shared_ptr<std::string> messageString);

  std::shared_ptr<IBoostWrapper> wrapper_;
  int socketNumber_;
  messagePairVec receivedMessages_;
  messageCounter messageCounter_;
  std::atomic<bool> stop_;

  SocketServicePtr readerWrapper_;
  SocketServicePtr writerWrapper_;

  ThreadPtr readerThread_;
  ThreadPtr writerThread_;
  
  Console console_;

  static const int noMessage_ = -1;

};

#endif