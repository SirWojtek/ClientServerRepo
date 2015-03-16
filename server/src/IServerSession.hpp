#ifndef I_SERVER_SESSION_HPP_
#define I_SERVER_SESSION_HPP_

#include <memory>

namespace std
{
	class thread;
}

class IServerSession
{
public:
  virtual std::shared_ptr<std::thread> start() = 0;
  virtual void startThreadsAndRun(std::shared_ptr<IServerSession> self) = 0;
  virtual void stop() = 0;
};

#endif