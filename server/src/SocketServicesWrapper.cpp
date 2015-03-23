#include "SocketServicesWrapper.hpp"

#include "common/socketServices/MessageReader.hpp"
#include "common/socketServices/MessageWriter.hpp"
#include "common/socketServices/MessageQueue.hpp"

void SocketServicesWrapper::createQueue()
{
	if (!queue_)
	{
		queue_ = std::make_shared<MessageQueue>();
	}
	else
	{
		console_.error << "Attempted to create messageQueue twice";
	}
}