#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <ctime>
#include "ServerSession.hpp"

using boost::asio::ip::tcp;

tcp::socket& ServerSession::socket()
{
	return socket_;
}

void ServerSession::start()
{
	boost::array<char, 2048> data;
    boost::system::error_code error;
    size_t length = socket_.read_some(boost::asio::buffer(data), error);
	if (error)
    	throw boost::system::system_error(error); // Some other error.

    if(data[length-1] == '\0') // 1.
    {
        console_.info << "Client sent a terminator";
        --length;
    }

    if(length) // 2.
    {
        console_.info << "echoing " << length;
        boost::asio::write(socket_, boost::asio::buffer(data, length));
    }
}
