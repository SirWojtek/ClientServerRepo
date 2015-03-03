#include <string>
#include <stdexcept>
#include <memory>
#include <iterator>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>

#include "TcpSocket.hpp"

using boost::asio::ip::tcp;

TcpSocket::TcpSocket() :
    ioService_(new boost::asio::io_service()),
    tcpSocket_(new tcp::socket(*ioService_)),
    console_("TcpSocket") {}

void TcpSocket::connect(const std::string& host, const std::string& port)
{
    tcp::resolver resolver(*ioService_);

    try
    {
        console_.info << "Trying to connect to host: " << host << port;
        boost::asio::connect(*tcpSocket_, resolver.resolve({ host, port }));
        console_.info << "Connected";
    }
    catch (boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
}

void TcpSocket::write(const char* message)
{
    std::string stringMessage(message);
    write(stringMessage);
}

void TcpSocket::write(std::string& message)
{
    try
    {
        message += iTcpSocketReadDelim;
        console_.debug << "Writing message:" << message;
        boost::asio::write(
            *tcpSocket_, boost::asio::buffer(message.c_str(), message.size()));
    }
    catch (boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
}

std::shared_ptr<const std::string> TcpSocket::read()
{
    boost::asio::streambuf buffer;

    try
    {
        console_.debug << "Waiting for message";
        if (!readWithTimeout(buffer))
        {
            return nullptr;
        }
    }
    catch (boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
    std::shared_ptr<std::string> message = getMessageFromBuffer(buffer);
    console_.debug << "Message received: " << *message;
    return message;
}

bool TcpSocket::readWithTimeout(boost::asio::streambuf& buffer)
{
    bool timeout = false;
    bool readed = false;
    boost::asio::deadline_timer timer(tcpSocket_->get_io_service(),
        boost::posix_time::seconds(iTcpSocketReadTimeout));
    timer.async_wait([&timeout](const boost::system::error_code& error)
    {
        timeout = true;
    });

    boost::asio::async_read_until(*tcpSocket_, buffer, iTcpSocketReadDelim,
        [&readed, this](const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            if (error == boost::asio::error::not_found)
            {
                throw std::runtime_error("Message readed from host is too large");
            }
            if (error != boost::asio::error::operation_aborted)
            {
                console_.debug << "bytes_transferred:" << bytes_transferred;
                readed = true;
            }
        });

    runIoService(readed, timeout, timer);

    return readed;
}

void TcpSocket::runIoService(const bool& readed, const bool& timeout,
    boost::asio::deadline_timer& timer)
{
    while(tcpSocket_->get_io_service().run_one())
    {
        if (readed)
        {
            timer.cancel();
        }
        else if (timeout)
        {
            tcpSocket_->cancel();
        }
    }
    tcpSocket_->get_io_service().reset();
}

std::shared_ptr<std::string> TcpSocket::getMessageFromBuffer(boost::asio::streambuf& buffer)
{
    std::string message((std::istreambuf_iterator<char>(&buffer)),
        std::istreambuf_iterator<char>());

    message.erase(std::remove(message.begin(), message.end(), iTcpSocketReadDelim),
        message.end());

    return std::make_shared<std::string>(message);
}

std::shared_ptr<boost::asio::ip::tcp::socket> TcpSocket::getSocket()
{
    std::shared_ptr<boost::asio::ip::tcp::socket> nullTcpPointer;
    return nullTcpPointer;
}
void TcpSocket::cancellAllAsyncServices() {}
