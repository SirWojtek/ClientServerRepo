#include <stdexcept>
#include "Server.hpp"

int main(int argc, char** argv)
{
	Server s;

	try
	{
		s.run();
	}
	catch(const std::runtime_error& e)
	{
		throw std::runtime_error(e.what());
	}
}