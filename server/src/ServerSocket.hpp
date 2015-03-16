#ifndef SERVER_SOCKET_HPP_
#define SERVER_SOCKET_HPP_

#include "common/socketServices/ITcpSocket.hpp"
#include "common/utilities/Console.hpp"

using boost::asio::ip::tcp;

class ServerSocket : public ITcpSocket
{
public:
	ServerSocket(std::shared_ptr<tcp::socket> tcpSocket) :
		tcpSocket_(tcpSocket),
		console_("ServerSocket")
	{ }
	void connect(const std::string& host, const std::string& port)
	{ }
    void write(std::string& message);
    void write(const char* message);
    std::shared_ptr<const std::string> read();
    std::shared_ptr<tcp::socket> getSocket();
    void cancellAllAsyncServices()
    { }


private:
    std::shared_ptr<tcp::socket> tcpSocket_;

    Console console_;

    const static size_t maxMessageSize = iTcpSocketMaxMessageSize;
    const static unsigned readTimeout = iTcpSocketReadTimeout;
    const static char readDelim = iTcpSocketReadDelim;

    char data_[maxMessageSize];
};

#endif