#include <fstream>
#include <iostream>
#include <chrono>
#include <mutex>

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

ILoger& InfoLoger::operator<<(bool val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(short val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(unsigned short val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(int val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(unsigned int val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(unsigned long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(long long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(unsigned long long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(float val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(double val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(long double val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(void* val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(const std::string& val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& InfoLoger::operator<<(const char* val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " INFO: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(bool val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(short val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(unsigned short val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(int val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(unsigned int val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(long val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(unsigned long val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(long long val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(unsigned long long val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(float val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(double val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(long double val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(void* val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(const std::string& val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& DebugLoger::operator<<(const char* val)
{
    if (debugPrint_ && !offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        printInfo(stream);
        stream << " DEBUG: " << val << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(bool val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(short val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(unsigned short val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(int val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(unsigned int val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(unsigned long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(long long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(unsigned long long val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(float val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(double val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(long double val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(void* val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(const std::string& val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}

ILoger& ErrorLoger::operator<<(const char* val)
{
    if (!offPrint_)
    {
        std::lock_guard<std::mutex> lockGuard(streamMutex_);
        std::ostream& stream = getStream();
        stream << "!!! ";
        printInfo(stream);
        stream << " ERROR: " << val << " !!!" << std::endl;
    }
    return *this;
}
