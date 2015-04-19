#ifndef THREAD_SAFE_OBJECT_HPP_
#define THREAD_SAFE_OBJECT_HPP_

#include <mutex>
#include <memory>

template<class T>
struct ThreadSafeObject
{
	ThreadSafeObject(T&& object) :
		object(std::move(object)),
		objectMutex(new std::mutex()) {}

	void lock()
	{
		objectMutex->lock();
	}

	void unlock()
	{
		objectMutex->unlock();
	}

	T object;
	std::unique_ptr<std::mutex> objectMutex;
};

#endif  // THREAD_SAFE_OBJECT_HPP_