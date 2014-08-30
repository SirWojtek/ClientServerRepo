#pragma once

#include <memory>
#include <thread>

#include "ITcpSocket.hpp"

typedef std::shared_ptr<std::thread> ThreadPtr;
class IMessageWriter
{
public:
	virtual ~IMessageWriter() {}
	virtual ThreadPtr start() = 0;
};
typedef std::shared_ptr<IMessageWriter> MessageWriterPtr;
