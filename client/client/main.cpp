#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <cereal/archives/json.hpp>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "TcpSocket.hpp"

int main(int argc, char** argv)
{
	Client client(new CommunicationService(new TcpSocket()));
	return client.start(argc, argv);
}
