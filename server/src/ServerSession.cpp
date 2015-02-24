#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "ServerSession.hpp"

using boost::asio::ip::tcp;

tcp::socket& ServerSession::socket()
{
	return *(socket_->getSocket());
}

void ServerSession::start()
{
    std::shared_ptr<const std::string> messageReceived = socket_->read();
    std::string messageToBeSent(*messageReceived);
    socket_->write(messageToBeSent);
	
}
