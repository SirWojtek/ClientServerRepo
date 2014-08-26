#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "Console.hpp"

int main(int argc, char** argv)
{
	ILoger::offPrint_ = true;
	::testing::InitGoogleMock(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::cout << std::endl;
	system("pause");
	return 0;
}