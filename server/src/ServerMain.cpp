#include <stdexcept>
#include <stdio.h>
#include <thread>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include "ServerInitializer.hpp"

void monitorKeyForQuittingServer(
  std::shared_ptr<boost::asio::io_service> ioService)
{
  char c;
  do
  {
    c=getchar();
    putchar(c);
  } while (c != 'q');
  ioService->reset();
  ioService->stop();
}

int main(int argc, char* argv[])
{
  try
  {
  	std::shared_ptr<boost::asio::io_service> ioService = 
      std::make_shared<boost::asio::io_service>();
    std::thread keyMonitor (boost::bind(monitorKeyForQuittingServer, ioService));
    ServerInitializer s(*ioService);
    s.runAsyncAccept();
    ioService->run();
    keyMonitor.join();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}