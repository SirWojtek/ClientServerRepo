#ifndef BOOST_WRAPPER_HPP_
#define BOOST_WRAPPER_HPP_

#include "IBoostWrapper.hpp"
#include <boost/asio.hpp>
#include "common/utilities/Console.hpp"

class BoostWrapper : public IBoostWrapper
{
public:
	BoostWrapper() :
	console_("BoostWrapper")
	{}

	void createIoService();
	void createAcceptor();
	void addSocket();
	int getLatestSocketNumber();
	void startAccepting(IServerSession& session,
		IServerInitializer* instance, int socketNumber);
	void runIoService();
	void resetIoService();
	void stopIoService();

	void write(std::string& message, int socketNumber);
	void write(const char* message);
	std::shared_ptr<const std::string> read(int socketNumber);

	void connect(const std::string& host, const std::string& port){}
	void cancellAllAsyncServices(){}
	void write(std::string& message){}
	std::shared_ptr<const std::string> read()
	{
		return std::shared_ptr<const std::string>();
	}

private:
	std::shared_ptr<boost::asio::io_service> ioService_;
	std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	std::vector<std::shared_ptr<boost::asio::ip::tcp::socket> > tcpSockets_;
	Console console_;

	const static size_t maxMessageSize = iBoostWrapperMaxMessageSize;
    const static unsigned readTimeout = iBoostWrapperReadTimeout;
    const static char readDelim = iBoostWrapperReadDelim;
    const static unsigned portNumber = iBoostWrapperPortNumber;
	char data_[maxMessageSize];

};

#endif