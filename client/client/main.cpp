#include <iostream>
#include <boost\asio\write.hpp>

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;

	std::shared_ptr<int> p1 = std::make_shared<int>(10);

	system("pause");
	return 0;
}
