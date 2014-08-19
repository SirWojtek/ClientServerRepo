#include <iostream>
#include <exception>

#include "Client.hpp"
#include "TcpSocket.hpp"
#include "ThreadFactory.hpp"

namespace test
{
	struct ConnectInfo
	{
		std::string host, port, message;
	};

	void testConnect(ConnectInfo info)
	{
		TcpSocket socket;

		try
		{
			socket.connect(info.host, info.port);
			socket.write(info.message);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

Client::Client(int argc, char** argv) :
	threadFactory_(new ThreadFactory()) {}

int Client::start()
{
	std::thread t = threadFactory_->startThread(test::testConnect,
		test::ConnectInfo({ "127.0.0.1", "1234", "hello" }));
	t.join();

	system("pause");
	return 0;
}

