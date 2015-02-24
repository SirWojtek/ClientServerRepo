#ifndef I_TCP_SOCKET_HPP_
#define I_TCP_SOCKET_HPP_

#include <string>
#include <memory>
#include <boost/asio.hpp>

class ITcpSocket
{
public:
	virtual ~ITcpSocket() {}
	virtual void connect(const std::string& host, const std::string& port) = 0;
	virtual void write(std::string& message) = 0;
	virtual void write(const char* message) = 0;
	virtual std::shared_ptr<const std::string> read() = 0;
	virtual std::shared_ptr<boost::asio::ip::tcp::socket> getSocket() = 0;
    virtual void cancellAllAsyncServices() = 0;

};
typedef std::shared_ptr<ITcpSocket> TcpSocketPtr;
const static size_t iTcpSocketMaxMessageSize = 8192;
const static unsigned iTcpSocketReadTimeout = 2;
const static char iTcpSocketReadDelim = ';';

#endif