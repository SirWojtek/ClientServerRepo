#ifndef I_BOOST_WRAPPER_HPP_
#define I_BOOST_WRAPPER_HPP_

#include "common/socketServices/ITcpSocket.hpp"
#include "IServerSession.hpp"
#include "IServerInitializer.hpp"

class IBoostWrapper : public ITcpSocket
{
public:
	virtual void connect(const std::string& host, const std::string& port) = 0;
	virtual void cancellAllAsyncServices() = 0;
	
	virtual void createAcceptor() = 0;
	virtual void createIoService() = 0;
	virtual void addSocket() = 0;
	virtual int getLatestSocketNumber() = 0;
	virtual void startAccepting(IServerSession& session,
		IServerInitializer* instance, int socketNumber) = 0;
	virtual void runIoService() = 0;
	virtual void resetIoService() = 0;
	virtual void stopIoService() = 0;

	virtual void write(std::string& message) = 0;
	virtual void write(std::string& message, int socketNumber) = 0;
	virtual void write(const char* message) = 0;
	virtual std::shared_ptr<const std::string> read() = 0;
	virtual std::shared_ptr<const std::string> read(int socketNumber) = 0;

};

typedef std::shared_ptr<IBoostWrapper> BoostWrapperPtr;
typedef std::shared_ptr<std::thread> ThreadPtr;
const static unsigned iBoostWrapperPortNumber = 4001;
const static size_t iBoostWrapperMaxMessageSize = 32768;
const static unsigned iBoostWrapperReadTimeout = 2;
const static char iBoostWrapperReadDelim = ';';

#endif