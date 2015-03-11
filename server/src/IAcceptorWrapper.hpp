#ifndef I_ACCEPTOR_WRAPPER_HPP_
#define I_ACCEPTOR_WRAPPER_HPP_

#include "ServerSession.hpp"
#include "IServerInitializer.hpp"

class IAcceptorWrapper{
public:
	virtual void createAcceptor() = 0;
	virtual std::shared_ptr<ServerSession> createServerSession() = 0;
	virtual void runIoService() = 0;
	virtual void startAccepting(ServerSession& session,
		IServerInitializer* instance) = 0;
};

#endif