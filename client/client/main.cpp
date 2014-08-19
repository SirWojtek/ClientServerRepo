#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <cereal/archives/json.hpp>

#include "Client.hpp"

int main(int argc, char** argv)
{
	Client client(argc, argv);
	return client.start();
}
