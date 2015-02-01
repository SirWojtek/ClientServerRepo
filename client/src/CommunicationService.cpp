#include <thread>
#include <string>
#include <memory>

#include "CommunicationService.hpp"
#include "NetworkMessage.hpp"

void CommunicationService::startService(
	const std::string& host, const std::string& port)
{
	tcpSocket_->connect(host, port);
	tcpSocket_ = nullptr;
	writerThread_ = messageWriter_->start();
}

void CommunicationService::putMessageInQueue(NetworkMessage&& message)
{
	messageQueue_->pushMessage(std::move(message));
	console_.info << "Message added to queue";
}

void CommunicationService::putMessageInQueue(const NetworkMessage& message)
{
	messageQueue_->pushMessage(message);
	console_.info << "Message added to queue";
}

void CommunicationService::tearDown()
{
	if (writerThread_->joinable())
	{
		messageQueue_->pushMessage({ MessageWriter::terminateCommand_, nullptr });
		writerThread_->join();
	}
}
