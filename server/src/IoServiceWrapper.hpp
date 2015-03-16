#ifndef IO_SERVICE_WRAPPER_HPP_
#define IO_SERVICE_WRAPPER_HPP_

#include <boost/asio/io_service.hpp>
#include "IIoServiceWrapper.hpp"

class IoServiceWrapper : public IIoServiceWrapper
{
public:
	IoServiceWrapper()
	{ }

	void createIoService();
	std::shared_ptr<boost::asio::io_service> getInstance();

protected:
	std::shared_ptr<boost::asio::io_service> ioService_;
};

#endif