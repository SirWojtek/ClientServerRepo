#ifndef TCP_SOCKET_STUB_HPP_
#define TCP_SOCKET_STUB_HPP_

#include "common/socketServices/ITcpSocket.hpp"

struct TcpSocketStub : public ITcpSocket
{
    void connect(const std::string& host, const std::string& port) override {}
    void write(std::string& message) override {}
    void write(std::string& message, int socketNumber) override {}
    void write(const char* message) override {}
    std::shared_ptr<const std::string> read() override
    {
        return nullptr;
    }
    std::shared_ptr<const std::string> read(int socketNumber) override
    {
        return nullptr;
    }
    void cancellAllAsyncServices() override {}
};

#endif  // TCP_SOCKET_STUB_HPP_
