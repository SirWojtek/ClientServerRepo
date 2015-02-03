#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "Console.hpp"

int main(int argc, char** argv)
{
	ILoger::offPrint_ = true;
	::testing::InitGoogleMock(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}