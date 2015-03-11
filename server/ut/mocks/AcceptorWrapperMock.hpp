#ifndef ACCEPTOR_WRAPPER_MOCK_HPP_
#define ACCEPTOR_WRAPPER_MOCK_HPP_

#include <memory>
#include <gmock/gmock.h>

#include "server/src/IAcceptorWrapper.hpp"

class AcceptorWrapperMock : public IAcceptorWrapper
{
public:
    MOCK_METHOD0(createAcceptor, void());
    MOCK_METHOD0(createServerSession, std::shared_ptr<ServerSession>());
    MOCK_METHOD0(runIoService, void());
    MOCK_METHOD2(startAccepting, void(ServerSession& session,
		IServerInitializer* instance));
};

#endif
