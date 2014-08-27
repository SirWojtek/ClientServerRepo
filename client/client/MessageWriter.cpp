#include <memory>
#include <thread>
#include <string>

#include "MessageWriter.hpp"

const std::string MessageWriter::terminateCommand_ = "TERMINATE";

std::thread MessageWriter::start()
{
	console_.info << "Starting writer thread";
	return std::thread(&MessageWriter::writerLoop, this, shared_from_this());
}

void MessageWriter::writerLoop(std::shared_ptr<MessageWriter> self)
{
	console_.info << "Writer thread start OK";
	while (true)
	{
		auto message = messageQueue_->popMessage();
		if (*message == terminateCommand_)
		{
			console_.debug << "Writer thread terminate";
			break;
		}
		console_.info << "Message to send: " << *message;

		tcpSocket_->write(*message);
		console_.info << "Message sended";

		auto answer = tcpSocket_->read();
		console_.info << "Received answer: " << *answer;
	}
}
