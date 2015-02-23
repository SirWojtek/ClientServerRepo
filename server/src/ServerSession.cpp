#include <boost/bind.hpp>
#include <ctime>
#include "ServerSession.hpp"

using boost::asio::ip::tcp;

tcp::socket& ServerSession::socket()
{
	return socket_;
}

void ServerSession::start()
{
	socket_.async_read_some(boost::asio::buffer(data_, maxLength),
		boost::bind(&ServerSession::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void ServerSession::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(data_, bytes_transferred),
			boost::bind(&ServerSession::handle_write, this,
				boost::asio::placeholders::error));
	}
	else
	{
		delete this;
	}
}

void ServerSession::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		socket_.async_read_some(boost::asio::buffer(data_, maxLength),
			boost::bind(&ServerSession::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		delete this;
	}
}
