#include <fstream>
#include <iostream>

#include "Console.hpp"

bool ILoger::debugPrint_ = false;
bool ILoger::filePrint_ = false;
std::ofstream ILoger::file_("client.log");
std::ostream& ILoger::console_ = std::cout;

void ILoger::setDebugPrint(bool status)
{
    debugPrint_ = status;
}
void ILoger::setFilePrint(bool status)
{
    filePrint_ = status;
}

std::ostream& ILoger::getStream() const
{
    return filePrint_ ? file_ : console_;
}

void ILoger::printClassName(std::ostream& stream) const
{
    stream << "[" << className_ << "]";
}

Console::Console(std::string className) :
    info_(new InfoLoger(className)),
    debug_(new DebugLoger(className)),
    error_(new ErrorLoger(className)),
    info(*info_),
    debug(*debug_),
    error(*error_) {}

const ILoger& InfoLoger::operator<<(bool val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(short val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned short val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(int val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned int val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(long val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned long val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(long long val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned long long val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(float val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(double val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(long double val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(void* val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(const std::string& val) const
{
    std::ostream& stream = getStream();
    printClassName(stream);
    stream << " INFO: " << val << std::endl;
    return *this;
}

const ILoger& InfoLoger::operator<<(const char* val) const
{
	std::ostream& stream = getStream();
	printClassName(stream);
	stream << " INFO: " << val << std::endl;
	return *this;
}

const ILoger& DebugLoger::operator<<(bool val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(short val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned short val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(int val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned int val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(long val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned long val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(long long val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned long long val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(float val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(double val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(long double val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(void* val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(const std::string& val) const
{
    if (debugPrint_)
    {
        std::ostream& stream = getStream();
        printClassName(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(const char* val) const
{
	if (debugPrint_)
	{
		std::ostream& stream = getStream();
		printClassName(stream);
		stream << " DEBUG: " << val << std::endl;
	}
	return *this;
}

const ILoger& ErrorLoger::operator<<(bool val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(short val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned short val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(int val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned int val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(long val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned long val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(long long val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned long long val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(float val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(double val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(long double val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(void* val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(const std::string& val) const
{
    std::ostream& stream = getStream();
    stream << "!!! ";
    printClassName(stream);
    stream << " ERROR: " << val << " !!!";
    return *this;
}

const ILoger& ErrorLoger::operator<<(const char* val) const
{
	std::ostream& stream = getStream();
	stream << "!!! ";
	printClassName(stream);
	stream << " ERROR: " << val << " !!!";
	return *this;
}
