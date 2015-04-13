#include "BoostWrapper.hpp"
#include <stdexcept>
#include <string>
#include <boost/bind.hpp>

#include "ServerSession.hpp"
#include "ServerInitializer.hpp"

void BoostWrapper::createIoService()
{
	if(ioService_ == nullptr)
	{
		ioService_ = std::make_shared<boost::asio::io_service>();
	}
}

void BoostWrapper::createAcceptor()
{
	if(ioService_ != nullptr && acceptor_ == nullptr)
	{
		acceptor_ = std::make_shared<boost::asio::ip::tcp::acceptor>(*ioService_,
        	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), BoostWrapper::portNumber));
	}
	else
	{
		throw std::runtime_error("Attempted to initialize acceptor twice.");
	}
}

void BoostWrapper::addSocket()
{
	tcpSockets_.push_back(std::make_shared<boost::asio::ip::tcp::socket>(*ioService_));
}

int BoostWrapper::getLatestSocketNumber()
{
    return (tcpSockets_.size() - 1);
}

void BoostWrapper::runIoService()
{
	ioService_->run();
}

void BoostWrapper::startAccepting(IServerSession& session,
		IServerInitializer* instance, int socketNumber)
{
	acceptor_->async_accept(*tcpSockets_[socketNumber],
     boost::bind(&IServerInitializer::handleAccept,
         instance, boost::asio::placeholders::error));
}

void BoostWrapper::resetIoService()
{
	ioService_->reset();
}

void BoostWrapper::stopIoService()
{
	ioService_->stop();
}

void BoostWrapper::write(std::string& message, int socketNumber)
{
    try
    {
        message += readDelim;
        console_.debug << "Writing message:" << message;
        boost::asio::write(
            *tcpSockets_[socketNumber], boost::asio::buffer(message.c_str(), message.size()));
    }
    catch (boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
}

void BoostWrapper::write(const char* message)
{
    std::string stringMessage(message);
    write(stringMessage);
}

std::shared_ptr<const std::string> BoostWrapper::read(int socketNumber)
{
    boost::system::error_code error;
    std::string message;
    message.reserve(maxMessageSize);
    size_t length = tcpSockets_[socketNumber]->read_some(boost::asio::buffer(data_, maxMessageSize), error);
	if (error)
	{
    	throw boost::system::system_error(error);
    }
    if(length)
    {
        std::shared_ptr<std::string> returnMessage = 
        	std::make_shared<std::string>(data_);
        return returnMessage;
    }
    std::shared_ptr<std::string> nullMessage;
    return nullMessage;
}
