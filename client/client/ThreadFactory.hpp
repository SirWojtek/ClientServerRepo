#pragma once

#include <thread>
#include <vector>
#include <memory>

class ThreadFactory
{
public:
	ThreadFactory() {}
	~ThreadFactory() {}

	template <class Function>
	std::thread startThread(Function&& func)
	{
		return std::thread(func);
	}

	template <class Function, class VarType>
	std::thread startThread(Function&& func, VarType&& var)
	{
		return std::thread(func, var);
	}

	template <class Function, class VarType>
	std::vector<std::thread> startThreadPool(
		unsigned size, Function&& func, VarType&& var)
	{
		std::vector<std::thread> pool;

		for (unsigned i = 0; i < size; i++)
			pool.push_back(std::thread(func, i, var));

		return pool;
	}

};
