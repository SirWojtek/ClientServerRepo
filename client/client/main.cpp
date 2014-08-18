#include <iostream>
#include <memory>

#include "TcpSocket.hpp"

int main(int argc, char** argv)
{
    TcpSocket socket;

	socket.connect("127.0.0.1", "2323");
    socket.write("hello!");

	system("pause");
	return 0;
}
