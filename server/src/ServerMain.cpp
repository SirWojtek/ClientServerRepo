#include <stdexcept>
#include <boost/asio.hpp>
#include "Server.hpp"

int main(int argc, char* argv[])
{
  try
  {
  	boost::asio::io_service ioService;
    Server s(ioService);
    ioService.run();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}