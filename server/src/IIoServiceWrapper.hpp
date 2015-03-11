#ifndef I_IO_SERVICE_WRAPPER_HPP_
#define I_IO_SERVICE_WRAPPER_HPP_

#include <boost/asio.hpp>

class IIoServiceWrapper{
public:
	virtual void createIoService() = 0;
	virtual std::shared_ptr<boost::asio::io_service> getInstance() = 0;
};

#endif