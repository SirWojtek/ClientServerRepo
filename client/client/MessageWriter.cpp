#include <memory>
#include <thread>
#include <string>

#include "MessageWriter.hpp"

const std::string MessageWriter::terminateCommand_ = "TERMINATE";

ThreadPtr MessageWriter::start()
{
	console_.info << "Starting writer thread";
	return std::make_shared<std::thread>(&MessageWriter::writerLoop, this, shared_from_this());
}

void MessageWriter::writerLoop(std::shared_ptr<MessageWriter> self)
{
	console_.info << "Writer thread start OK";
	while (true)
	{
		auto netMessage = messageQueue_->popMessage();
		if (netMessage->message == terminateCommand_)		
			break;

		writeMessage(netMessage);
		receiveAnswer(netMessage);
	}
	console_.debug << "Writer thread ended";
}

void MessageWriter::writeMessage(NetworkMessagePtr netMessage)
{
	console_.info << "Message to send: " << netMessage->message;
	tcpSocket_->write(netMessage->message);
	console_.info << "Message sended";
}

void MessageWriter::receiveAnswer(NetworkMessagePtr netMessage)
{
	if (netMessage->callback)
	{
		auto answer = tcpSocket_->read();
		console_.info << "Received answer: " << *answer;

		netMessage->callback(answer);
		console_.debug << "Return from callback function";
	}
}
