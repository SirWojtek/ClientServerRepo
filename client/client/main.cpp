#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <cereal/archives/json.hpp>

#include "Client.hpp"
#include "TcpSocket.hpp"
#include "MessageQueue.hpp"

int main(int argc, char** argv)
{

	Client client(std::make_shared<TcpSocket>());
	return client.start(argc, argv);
}
