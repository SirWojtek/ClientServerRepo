#pragma once

#include <memory>
#include <thread>

#include "ITcpSocket.hpp"

class IMessageWriter
{
public:
	virtual ~IMessageWriter() {}
	virtual std::thread start() = 0;
};
typedef std::shared_ptr<IMessageWriter> MessageWriterPtr;
