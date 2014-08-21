#pragma once

#include <memory>
#include <future>

#include "ITcpSocket.hpp"

class CommunicationService
{
public:
	CommunicationService(ITcpSocket* tcpSocket) :
		tcpSocket_(tcpSocket) {}

	void startService();

private:
	std::shared_ptr<ITcpSocket> tcpSocket_;
};

