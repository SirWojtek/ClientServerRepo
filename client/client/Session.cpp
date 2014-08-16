#include "Session.h"


Session::Session()
{
}


Session::~Session()
{
}

std::shared_ptr<ISession> Session::getSession()
{
	return std::shared_ptr<ISession>(new Session());
}

void Session::start()
{
}
