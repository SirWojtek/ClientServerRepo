#include <future>
#include <string>
#include <exception>
#include <memory>

#include "CommunicationService.hpp"

void CommunicationService::startService(
	const std::string& host, const std::string& port)
{
	try
	{
		initService(host, port);
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
