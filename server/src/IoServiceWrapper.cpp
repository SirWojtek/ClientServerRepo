#include "IoServiceWrapper.hpp"

#include <stdexcept>

void IoServiceWrapper::createIoService()
	{
		ioService_ = std::make_shared<boost::asio::io_service>();
	}

std::shared_ptr<boost::asio::io_service> IoServiceWrapper::getInstance()
	{
		if (ioService_ != nullptr)
		{
			return ioService_;
		}
		throw std::invalid_argument("Attepted to get ininitialized ioService object.");
	}