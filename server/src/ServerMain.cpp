#include <stdexcept>
#include <stdio.h>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "BoostWrapper.hpp"
#include "ServerInitializer.hpp"

void monitorKeyForQuittingServer(BoostWrapper& wrapper)
{
  char c;
  do
  {
    c=getchar();
    putchar(c);
  } while (c != 'q');
  wrapper.resetIoService();
  wrapper.stopIoService();
}

int main(int argc, char* argv[])
{
  try
  {
    ILoger::setDebugPrint(false);


  	std::shared_ptr<BoostWrapper> wrapper =
      std::make_shared<BoostWrapper>();
    wrapper->createIoService();
    wrapper->createAcceptor();
    wrapper->addSocket();
    std::thread keyMonitor (boost::bind(monitorKeyForQuittingServer,
      *wrapper));
    ServerInitializer s(wrapper);
    s.runAsyncAccept();
    wrapper->runIoService();
    keyMonitor.join();
    s.joinThreads();
  }
  catch(const std::runtime_error& e)
  {
    throw std::runtime_error(e.what());
  }
  
  return 0;
}