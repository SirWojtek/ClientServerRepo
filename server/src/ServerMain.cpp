#include <stdexcept>
#include <stdio.h>
#include <thread>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include "ServerInitializer.hpp"

#include "AcceptorWrapper.hpp"
#include "IoServiceWrapper.hpp"

void monitorKeyForQuittingServer(IoServiceWrapper& ioService)
{
  char c;
  do
  {
    c=getchar();
    putchar(c);
  } while (c != 'q');
  ioService.getInstance()->reset();
  ioService.getInstance()->stop();
}

int main(int argc, char* argv[])
{
  try
  {
  	std::shared_ptr<IoServiceWrapper> ioService = 
      std::make_shared<IoServiceWrapper>();
    ioService->createIoService();
    std::thread keyMonitor (boost::bind(monitorKeyForQuittingServer,
      *ioService));
    std::shared_ptr<AcceptorWrapper> acceptor
    = std::make_shared<AcceptorWrapper>(ioService->getInstance());
    acceptor->createAcceptor();
    ServerInitializer s(acceptor);
    s.runAsyncAccept();
    ioService->getInstance()->run();
    keyMonitor.join();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}