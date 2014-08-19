#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <cereal/archives/json.hpp>

#include "TcpSocket.hpp"

void testConnect(std::string host, std::string port, std::string message)
{
	TcpSocket socket;

	socket.connect(host, port);
	socket.write(message);
	auto resp = socket.read();
	std::cout << *resp;
}

int main(int argc, char** argv)
{
	try
	{
		testConnect("127.0.0.1", "1234", "hello!");
	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	system("pause");
	return 0;
}
