#pragma once
#include <memory>

class ISession
{
public:
	ISession() {}
	virtual ~ISession() {}
	virtual std::shared_ptr<ISession> getSession() = 0;
	virtual void start() = 0;
};

class Session : public ISession
{
public:
	virtual ~Session();
	virtual std::shared_ptr<ISession> getSession();
	virtual void start();

private:
	Session();
};

