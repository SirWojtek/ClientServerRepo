#include <iostream>
#include <memory>
#include <cereal/archives/json.hpp>

#include "TcpSocket.hpp"

int main(int argc, char** argv)
{
    TcpSocket socket;

	socket.connect("127.0.0.1", "1234");
    socket.write("hello!");

	system("pause");
	return 0;
}
