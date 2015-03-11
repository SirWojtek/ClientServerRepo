#ifndef IO_SERVICE_WRAPPER_MOCK_HPP_
#define IO_SERVICE_WRAPPER_MOCK_HPP_

#include <memory>
#include <gmock/gmock.h>

#include "server/src/IIoServiceWrapper.hpp"

class IoServiceWrapperMock : public IIoServiceWrapper
{
public:
    MOCK_METHOD0(createIoService, void());
    MOCK_METHOD0(getInstance, boost::asio::io_service&());
};

using IoServiceWrapperMockPtr = std::shared_ptr<IoServiceWrapperMock>;

#endif
