#ifndef IO_SERVICE_WRAPPER_HPP_
#define IO_SERVICE_WRAPPER_HPP_

#include <stdexcept>
#include <boost/asio/io_service.hpp>
#include "IIoServiceWrapper.hpp"

class IoServiceWrapper : public IIoServiceWrapper
{
public:
	IoServiceWrapper()
	{ }

	void createIoService()
	{
		ioService_ = std::make_shared<boost::asio::io_service>();
	}
	
	std::shared_ptr<boost::asio::io_service> getInstance()
	{
		if (ioService_ != nullptr)
		{
			return ioService_;
		}
		throw std::invalid_argument("Attepted to get ininitialized ioService object.");
	}

protected:
	std::shared_ptr<boost::asio::io_service> ioService_;
};

#endif