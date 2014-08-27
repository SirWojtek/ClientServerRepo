#include <thread>
#include <string>
#include <exception>
#include <memory>

#include "CommunicationService.hpp"

void CommunicationService::startService(
	const std::string& host, const std::string& port)
{
	try
	{
		writerThread_ = initService(host, port);
	}
	catch (std::runtime_error& e)
	{
		console_.error << e.what();
	}
}

std::thread CommunicationService::initService(std::string host, std::string port)
{
	tcpSocket_->connect(host, port);
	tcpSocket_ = nullptr;
	return messageWriter_->start();
}

void CommunicationService::putMessageInQueue(std::string&& message)
{
	messageQueue_->pushMessage(std::move(message));
	console_.info << "Message added to queue";
}

void CommunicationService::tearDown()
{
	std::string terminateCommand(MessageWriter::terminateCommand_);
	messageQueue_->pushMessage(std::move(terminateCommand));
	writerThread_.join();
}
