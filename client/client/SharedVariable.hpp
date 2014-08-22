#pragma once

#include <mutex>
#include <condition_variable>
#include <memory>

template<class VarType>
class SharedVariable
{
public:
	SharedVariable() :
		variable_(std::make_shared<VarType>()) {}
	SharedVariable(std::shared_ptr<VarType> var) :
		variable_(var) {}

	bool tryLock()
	{
		return mutex_.try_lock();
	}

	std::unique_lock<std::mutex> getUniqueLock()
	{
		return std::unique_lock<std::mutex>(mutex_);
	}

	void wait(std::unique_lock<std::mutex>& lock)
	{
		conditional_.wait(lock);
	}

	void notify()
	{
		conditional_.notify_one();
	}

	void notifyAll()
	{
		conditional_.notify_all();
	}

	std::shared_ptr<VarType> get()
	{
		return variable_;
	}

	void set(VarType&& var)
	{
		*variable_ = var;
	}

private:
	std::mutex mutex_;
	std::condition_variable conditional_;
	std::shared_ptr<VarType> variable_;
};


