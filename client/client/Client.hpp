#pragma once

#include <memory>

#include "ThreadFactory.hpp"
#include "SharedVariable.hpp"

class Client
{
public:
	Client(int argc, char** argv);
	~Client() {}

	int start();

private:
	std::unique_ptr<ThreadFactory> threadFactory_;
};

