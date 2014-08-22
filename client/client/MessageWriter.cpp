#include <memory>

#include "MessageWriter.hpp"

void MessageWriter::asyncSend(std::shared_ptr<std::string> message)
{
	console_.debug << "Starting async write message";
	writerThread_ = std::async(&MessageWriter::sendMessage, this, message);
}

bool MessageWriter::sendMessage(std::shared_ptr<std::string> message)
{

	console_.debug << "Mesage sended: " << *message;
	return true;
}

bool MessageWriter::asyncGet()
{
	return writerThread_.get();
}
