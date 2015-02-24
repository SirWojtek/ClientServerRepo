#include <stdexcept>
#include <boost/asio.hpp>
#include "ServerInitializer.hpp"

int main(int argc, char* argv[])
{
  try
  {
  	boost::asio::io_service ioService;
    ServerInitializer s(ioService);
    ioService.run();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}