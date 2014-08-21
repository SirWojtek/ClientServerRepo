#pragma once

#include <ostream>
#include <fstream>
#include <string>
#include <memory>

class ILoger{
public:
    ILoger(std::string className) : className_(className) {}

    virtual const ILoger& operator<<(bool val) const = 0;
    virtual const ILoger& operator<<(short val) const = 0;
    virtual const ILoger& operator<<(unsigned short val) const = 0;
    virtual const ILoger& operator<<(int val) const = 0;
    virtual const ILoger& operator<<(unsigned int val) const = 0;
    virtual const ILoger& operator<<(long val) const = 0;
    virtual const ILoger& operator<<(unsigned long val) const = 0;
    virtual const ILoger& operator<<(long long val) const = 0;
    virtual const ILoger& operator<<(unsigned long long val) const = 0;
    virtual const ILoger& operator<<(float val) const = 0;
    virtual const ILoger& operator<<(double val) const = 0;
    virtual const ILoger& operator<<(long double val) const = 0;
    virtual const ILoger& operator<<(void* val) const = 0;
    virtual const ILoger& operator<<(const std::string& val) const = 0;

    static void setDebugPrint(bool status);
    static void setFilePrint(bool status);

protected:
    void printClassName(std::ostream& stream) const;
    std::ostream& getStream() const;

    static bool debugPrint_;

private:
    const std::string className_;
    static bool filePrint_;
    static std::ofstream file_;
    static std::ostream& console_;
};

class InfoLoger : public ILoger
{
public:
    InfoLoger(std::string className) : ILoger(className) {}

    const ILoger& operator<<(bool val) const;
    const ILoger& operator<<(short val) const;
    const ILoger& operator<<(unsigned short val) const;
    const ILoger& operator<<(int val) const;
    const ILoger& operator<<(unsigned int val) const;
    const ILoger& operator<<(long val) const;
    const ILoger& operator<<(unsigned long val) const;
    const ILoger& operator<<(long long val) const;
    const ILoger& operator<<(unsigned long long val) const;
    const ILoger& operator<<(float val) const;
    const ILoger& operator<<(double val) const;
    const ILoger& operator<<(long double val) const;
    const ILoger& operator<<(void* val) const;
    const ILoger& operator<<(const std::string& val) const;
};

class DebugLoger : public ILoger
{
public:
    DebugLoger(std::string className) : ILoger(className) {}

    const ILoger& operator<<(bool val) const;
    const ILoger& operator<<(short val) const;
    const ILoger& operator<<(unsigned short val) const;
    const ILoger& operator<<(int val) const;
    const ILoger& operator<<(unsigned int val) const;
    const ILoger& operator<<(long val) const;
    const ILoger& operator<<(unsigned long val) const;
    const ILoger& operator<<(long long val) const;
    const ILoger& operator<<(unsigned long long val) const;
    const ILoger& operator<<(float val) const;
    const ILoger& operator<<(double val) const;
    const ILoger& operator<<(long double val) const;
    const ILoger& operator<<(void* val) const;
    const ILoger& operator<<(const std::string& val) const;
};

class ErrorLoger : public ILoger
{
public:
    ErrorLoger(std::string className) : ILoger(className) {}

    const ILoger& operator<<(bool val) const;
    const ILoger& operator<<(short val) const;
    const ILoger& operator<<(unsigned short val) const;
    const ILoger& operator<<(int val) const;
    const ILoger& operator<<(unsigned int val) const;
    const ILoger& operator<<(long val) const;
    const ILoger& operator<<(unsigned long val) const;
    const ILoger& operator<<(long long val) const;
    const ILoger& operator<<(unsigned long long val) const;
    const ILoger& operator<<(float val) const;
    const ILoger& operator<<(double val) const;
    const ILoger& operator<<(long double val) const;
    const ILoger& operator<<(void* val) const;
    const ILoger& operator<<(const std::string& val) const;
};

class Console
{
public:
    Console(std::string className);

private:
    std::unique_ptr<const ILoger> info_;
    std::unique_ptr<const ILoger> debug_;
    std::unique_ptr<const ILoger> error_;

public:
    const ILoger& info;
    const ILoger& debug;
    const ILoger& error;
};