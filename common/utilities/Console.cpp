#include <fstream>
#include <iostream>
#include <chrono>

#include "Console.hpp"

bool ILoger::debugPrint_ = true;
bool ILoger::filePrint_ = false;
bool ILoger::offPrint_ = false;
std::ofstream ILoger::file_("run.log");
std::ostream& ILoger::console_ = std::cout;

void ILoger::setDebugPrint(bool status)
{
    debugPrint_ = status;
}

void ILoger::setFilePrint(bool status)
{
    filePrint_ = status;
}

void ILoger::setOffPrint(bool status)
{
    offPrint_ = status;
}

std::ostream& ILoger::getStream() const
{
    return filePrint_ ? file_ : console_;
}

void ILoger::printInfo(std::ostream& stream) const
{
    using namespace std::chrono;

    stream << duration_cast<milliseconds>(
        high_resolution_clock::now().time_since_epoch()).count()
        << " [" << className_ << "]";
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
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(short val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned short val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(int val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned int val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(long long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(unsigned long long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(float val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(double val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(long double val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(void* val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(const std::string& val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& InfoLoger::operator<<(const char* val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(bool val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(short val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned short val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(int val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned int val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(long val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned long val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(long long val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(unsigned long long val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(float val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(double val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(long double val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(void* val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(const std::string& val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& DebugLoger::operator<<(const char* val) const
{
    if (debugPrint_ && !offPrint_)
    {
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(bool val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(short val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned short val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(int val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned int val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(long long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(unsigned long long val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(float val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(double val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(long double val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(void* val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(const std::string& val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

const ILoger& ErrorLoger::operator<<(const char* val) const
{
    if (!offPrint_)
    {
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}
