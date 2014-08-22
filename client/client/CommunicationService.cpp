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

	}
	catch (std::runtime_error& e)
	{
		console_.error << e.what();
	}
}

void CommunicationService::initService(std::string host, std::string port)
{
	tcpSocket_->connect(host, port);
}
