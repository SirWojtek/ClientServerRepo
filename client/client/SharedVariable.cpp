#include <mutex>
#include <condition_variable>

#include "SharedVariable.hpp"

template<class VarType>
bool SharedVariable<VarType>::tryLock()
{
	return mutex_.try_lock();
}

template<class VarType>
void SharedVariable<VarType>::lock()
{
	mutex_.lock();
}

template<class VarType>
void SharedVariable<VarType>::unlock()
{
	mutex_.unlock();
}

template<class VarType>
std::mutex SharedVariable<VarType>::getMutex()
{
	return mutex_;
}

template<class VarType>
void SharedVariable<VarType>::wait()
{
	conditional_.wait();
}

template<class VarType>
void SharedVariable<VarType>::notify()
{
	conditional_.notify_one();
}

template<class VarType>
void SharedVariable<VarType>::notifyAll()
{
	conditional_.notify_all();
}

template<class VarType>
VarType SharedVariable<VarType>::get()
{
	return variable_;
}

template<class VarType>
void SharedVariable<VarType>::set(VarType var)
{
	variable_ = var;
}
