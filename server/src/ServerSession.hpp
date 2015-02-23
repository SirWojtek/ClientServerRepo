#ifndef SERVER_SESSION_HPP_
#define SERVER_SESSION_HPP_

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "common/utilities/Console.hpp"

using boost::asio::ip::tcp;

class ServerSession : public boost::enable_shared_from_this<ServerSession>
{
public:
  ServerSession(boost::asio::io_service& io_service):
    socket_(io_service),
    console_("ServerSession")
  { }

  tcp::socket& socket();
  void start();
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  void handle_write(const boost::system::error_code& error);

private:
  tcp::socket socket_;
  enum { maxLength = 1024 };
  char data_[maxLength];
  Console console_;

};

#endif