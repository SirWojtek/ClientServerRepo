#include <future>
#include <string>
#include <exception>
#include <memory>

#include "CommunicationService.hpp"

void CommunicationService::startService()
{
	try
	{
		// initService("127.0.0.1", "1234");

		while (true)
		{
			console_.debug << "aa";
			workTick();
			if (!messageWriter_->asyncGet())
				throw std::runtime_error("Message sending error");
		}
	}
	catch (std::runtime_error& e)
	{
		console_.error << e.what();
	}
}

void CommunicationService::workTick()
{
	auto message = getMessage();
	messageWriter_->asyncSend(message);
}

void CommunicationService::initService(std::string host, std::string port)
{
	tcpSocket_->connect(host, port);
}

std::shared_ptr<std::string> CommunicationService::getMessage()
{
	auto lock = messageQueue_->getUniqueLock();
	while (messageQueue_->get()->isEmpty()) messageQueue_->wait(lock);
	auto message = messageQueue_->get()->popMessage();

	return message;
}
