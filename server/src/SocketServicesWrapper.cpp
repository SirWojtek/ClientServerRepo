#include "SocketServicesWrapper.hpp"

#include "common/socketServices/MessageReader.hpp"
#include "common/socketServices/MessageWriter.hpp"

void SocketServicesWrapper::createReaderForQueue(
	std::shared_ptr<IBoostWrapper> boostWrapper, int socketNumber)
{
	if (commanderExists())
	{
		console_.error << "Tried to create commander(reader) without queue or create commander twice";
	}
	else
	{
		commander_ = std::make_shared<MessageReader>(boostWrapper, queue_, socketNumber);
	}
}

void SocketServicesWrapper::createWriterForQueue(
	std::shared_ptr<IBoostWrapper> boostWrapper, int socketNumber)
{
	if (commanderExists())
	{
		console_.error << "Tried to create commander(writer) without queue or create commander twice";
	}
	else
	{
		commander_ = std::make_shared<MessageWriter>(boostWrapper, queue_, socketNumber);
	}
}

std::shared_ptr<std::thread> SocketServicesWrapper::startCommander()
{
	if (commanderExists())
	{
		return commander_->start();
	}
	console_.error << "Tried to start uninitialized commander";
	return std::shared_ptr<std::thread>();
}

void SocketServicesWrapper::pushMessage(const std::string& message)
{
	queue_->pushMessage(message);
}

std::shared_ptr<std::string> SocketServicesWrapper::popMessage()
{
	return queue_->popMessage();
}

void SocketServicesWrapper::waitForEmptyQueue()
{
	queue_->waitForEmptyQueue();
}

void SocketServicesWrapper::waitForEmptyQueueWithTimeout()
{
	queue_->waitForEmptyQueueWithTimeout();
}

bool SocketServicesWrapper::commanderExists()
{
	if (commander_)
	{
		return true;
	}
	return false;
}
