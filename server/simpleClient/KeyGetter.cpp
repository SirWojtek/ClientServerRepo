#include "KeyGetter.hpp"
#include <unistd.h>
#include <chrono>
#include <thread>

KeyGetter::KeyGetter()
{ }

KeyGetter::~KeyGetter()
{ }

char KeyGetter::getPressedKey() const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return static_cast<char>('w');
}




