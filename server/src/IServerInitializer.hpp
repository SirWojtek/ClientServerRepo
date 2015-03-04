#ifndef I_SERVER_INITIALIZER_HPP_
#define I_SERVER_INITIALIZER_HPP_

class IServerInitializer
{
public:
	virtual void handleAccept(const boost::system::error_code& error) = 0;
	virtual void runAsyncAccept() = 0;
};

#endif