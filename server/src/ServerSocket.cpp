#include <string>
#include <exception>
#include <memory>
#include <istream>
#include <sstream>

#include "ServerSocket.hpp"

std::shared_ptr<tcp::socket> ServerSocket::getSocket()
{
	return tcpSocket_;
}

void ServerSocket::write(const char* message)
{
    std::string stringMessage(message);
    write(stringMessage);
}

void ServerSocket::write(std::string& message)
{
    try
    {
        message += readDelim;
        boost::asio::write(
            *tcpSocket_, boost::asio::buffer(message.c_str(), message.size()));
    }
    catch (boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
}

std::shared_ptr<const std::string> ServerSocket::read()
{
    boost::system::error_code error;
    std::string message;
    message.reserve(maxMessageSize);
    size_t length = tcpSocket_->read_some(boost::asio::buffer(data_, maxMessageSize), error);
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