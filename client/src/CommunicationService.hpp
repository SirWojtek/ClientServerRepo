#ifndef COMMUNICATION_SERVICE_HPP_
#define COMMUNICATION_SERVICE_HPP_

#include <memory>
#include <thread>
#include <string>

#include "ICommunicationService.hpp"
#include "NetworkMessage.hpp"
#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"
#include "IMessageCommander.hpp"
#include "Console.hpp"

class CommunicationService : public ICommunicationService
{
public:
	CommunicationService(TcpSocketPtr tcpSocket,
		MessageQueuePtr writerQueue, MessageCommanderPtr messageWritter,
		MessageQueuePtr readerQueue, MessageCommanderPtr messageReader) :
			tcpSocket_(std::move(tcpSocket)),
			writerQueue_(writerQueue),
			messageWriter_(messageWritter),
			readerQueue_(readerQueue),
			messageReader_(messageReader),
			console_("CommunicationService") {}

	void startService(const std::string& host, const std::string& port);
	void putMessageInQueue(NetworkMessage&& message);
	void putMessageInQueue(const NetworkMessage& message);
	void tearDown();

private:
	TcpSocketPtr tcpSocket_;

	MessageQueuePtr writerQueue_;
	MessageCommanderPtr messageWriter_;
	ThreadPtr writerThread_;

	MessageQueuePtr readerQueue_;
	MessageCommanderPtr messageReader_;
	ThreadPtr readerThread_;

	Console console_;
};

#endif  // COMMUNICATION_SERVICE_HPP_
