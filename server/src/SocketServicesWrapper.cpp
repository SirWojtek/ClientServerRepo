#include "SocketServicesWrapper.hpp"

#include "common/socketServices/MessageReader.hpp"
#include "common/socketServices/MessageWriter.hpp"
#include "common/socketServices/MessageQueue.hpp"

void SocketServicesWrapper::createQueue()
{
	if (!queueExists())
	{
		queue_ = std::make_shared<MessageQueue>();
	}
	else
	{
		console_.error << "Attempted to create messageQueue twice";
	}
}

void SocketServicesWrapper::createReaderForQueue(
	std::shared_ptr<IBoostWrapper> boostWrapper, int socketNumber)
{
	if (commanderExists() || !queueExists())
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
	if (commanderExists() || !queueExists())
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
	if (queueExists())
	{
		queue_->pushMessage(message);
	}
	else
	{
		console_.error << "Tried to push message on uninitialized queue";
	}
}

std::shared_ptr<std::string> SocketServicesWrapper::popMessage()
{
	if (queueExists())
	{
		return queue_->popMessage();
	}
	console_.error << "Tried to pop message from uninitialized queue";
	return std::shared_ptr<std::string>();
}

void SocketServicesWrapper::waitForEmptyQueue()
{
	if (queueExists())
	{
		queue_->waitForEmptyQueue();
	}
	else
	{
		console_.error << "Tried to wait on uninitialized queue";
	}
}

void SocketServicesWrapper::waitForEmptyQueueWithTimeout()
{
	if (queueExists())
	{
		queue_->waitForEmptyQueueWithTimeout();
	}
	else
	{
		console_.error << "Tried to wait on uninitialized queue (with timeout)";
	}
}

bool SocketServicesWrapper::commanderExists()
{
	if (commander_)
	{
		return true;
	}
	return false;
}

bool SocketServicesWrapper::queueExists()
{
	if (queue_)
	{
		return true;
	}
	return false;
}