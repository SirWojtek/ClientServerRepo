#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <ostream>
#include <fstream>
#include <string>
#include <memory>
#include <mutex>

class ILoger{
public:
    ILoger(std::string className) : className_(className) {}

    virtual ILoger& operator<<(bool val) = 0;
    virtual ILoger& operator<<(short val) = 0;
    virtual ILoger& operator<<(unsigned short val) = 0;
    virtual ILoger& operator<<(int val) = 0;
    virtual ILoger& operator<<(unsigned int val) = 0;
    virtual ILoger& operator<<(long val) = 0;
    virtual ILoger& operator<<(unsigned long val) = 0;
    virtual ILoger& operator<<(long long val) = 0;
    virtual ILoger& operator<<(unsigned long long val) = 0;
    virtual ILoger& operator<<(float val) = 0;
    virtual ILoger& operator<<(double val) = 0;
    virtual ILoger& operator<<(long double val) = 0;
    virtual ILoger& operator<<(void* val) = 0;
    virtual ILoger& operator<<(const std::string& val) = 0;
	virtual ILoger& operator<<(const char* val) = 0;

    static void setDebugPrint(bool status);
    static void setFilePrint(bool status);
	static void setOffPrint(bool status);

	static bool debugPrint_;
	static bool offPrint_;
	static bool filePrint_;
	static std::ofstream file_;
	static std::ostream& console_;

protected:
    void printInfo(std::ostream& stream) const;
    std::ostream& getStream() const;

    const std::string className_;
    std::mutex streamMutex_;
};

class InfoLoger : public ILoger
{
public:
    InfoLoger(std::string className) : ILoger(className) {}

    ILoger& operator<<(bool val);
    ILoger& operator<<(short val);
    ILoger& operator<<(unsigned short val);
    ILoger& operator<<(int val);
    ILoger& operator<<(unsigned int val);
    ILoger& operator<<(long val);
    ILoger& operator<<(unsigned long val);
    ILoger& operator<<(long long val);
    ILoger& operator<<(unsigned long long val);
    ILoger& operator<<(float val);
    ILoger& operator<<(double val);
    ILoger& operator<<(long double val);
    ILoger& operator<<(void* val);
    ILoger& operator<<(const std::string& val);
	ILoger& operator<<(const char* val);
};

class DebugLoger : public ILoger
{
public:
    DebugLoger(std::string className) : ILoger(className) {}

    ILoger& operator<<(bool val);
    ILoger& operator<<(short val);
    ILoger& operator<<(unsigned short val);
    ILoger& operator<<(int val);
    ILoger& operator<<(unsigned int val);
    ILoger& operator<<(long val);
    ILoger& operator<<(unsigned long val);
    ILoger& operator<<(long long val);
    ILoger& operator<<(unsigned long long val);
    ILoger& operator<<(float val);
    ILoger& operator<<(double val);
    ILoger& operator<<(long double val);
    ILoger& operator<<(void* val);
    ILoger& operator<<(const std::string& val);
	ILoger& operator<<(const char* val);
};

class ErrorLoger : public ILoger
{
public:
    ErrorLoger(std::string className) : ILoger(className) {}

    ILoger& operator<<(bool val);
    ILoger& operator<<(short val);
    ILoger& operator<<(unsigned short val);
    ILoger& operator<<(int val);
    ILoger& operator<<(unsigned int val);
    ILoger& operator<<(long val);
    ILoger& operator<<(unsigned long val);
    ILoger& operator<<(long long val);
    ILoger& operator<<(unsigned long long val);
    ILoger& operator<<(float val);
    ILoger& operator<<(double val);
    ILoger& operator<<(long double val);
    ILoger& operator<<(void* val);
    ILoger& operator<<(const std::string& val);
	ILoger& operator<<(const char* val);
};

class Console
{
public:
    Console(std::string className);

private:
    std::shared_ptr<ILoger> info_;
    std::shared_ptr<ILoger> debug_;
    std::shared_ptr<ILoger> error_;

public:
    ILoger& info;
    ILoger& debug;
    ILoger& error;
};

#endif  // CONSOLE_HPP_
