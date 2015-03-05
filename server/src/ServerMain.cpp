#include <stdexcept>
#include <stdio.h>
#include <thread>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include "ServerInitializer.hpp"

void monitorKeyForQuittingServer(IoServiceWrapper& ioService)
{
  char c;
  do
  {
    c=getchar();
    putchar(c);
  } while (c != 'q');
  ioService.getInstance().reset();
  ioService.getInstance().stop();
}

int main(int argc, char* argv[])
{
  try
  {
  	IoServiceWrapper ioService;
    ioService.createIoService();
    std::thread keyMonitor (boost::bind(monitorKeyForQuittingServer, ioService));
    ServerInitializer s(ioService);
    s.runAsyncAccept();
    ioService.getInstance().run();
    keyMonitor.join();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}