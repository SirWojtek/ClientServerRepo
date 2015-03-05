#ifndef ACCEPTOR_WRAPPER_MOCK_HPP_
#define ACCEPTOR_WRAPPER_MOCK_HPP_

#include <memory>
#include <gmock/gmock.h>

#include "server/src/IAcceptorWrapper.hpp"

class AcceptorWrapperMock : public IAcceptorWrapper
{
public:
    MOCK_METHOD1(createAcceptor, void(boost::asio::io_service& ioService);
    MOCK_METHOD0(getInstance, boost::asio::ip::tcp::acceptor&());
};

#endif
