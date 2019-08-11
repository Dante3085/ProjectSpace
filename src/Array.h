#pragma once

#include "Log.h"

template <class T>
class Array
{
public:
	Array(int size) : size{size}, a { new T[size] } {}

	T& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			using namespace ProjectSpace;
			Log::getInstance() << lo::PTC << ll::ERR << lo::TIMESTAMP << "Invalid Index: " << index << lo::STACKTRACE << lo::END
				<< lo::EXIT;
		}
		return a[index];
	}

private:
	int size;
	T* a;
};