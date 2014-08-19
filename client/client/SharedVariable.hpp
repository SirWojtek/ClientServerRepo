#pragma once
#include <mutex>
#include <condition_variable>

template<class VarType>
class SharedVariable
{
public:
	SharedVariable() {}
	SharedVariable(VarType var) :
		variable_(var) {}
	~SharedVariable() {}

	bool tryLock();
	void lock();
	void unlock();
	std::mutex getMutex();

	void wait();
	void notify();
	void notifyAll();

	VarType get();
	void set(VarType var);
private:
	std::mutex mutex_;
	std::condition_variable conditional_;
	VarType variable_;
};


