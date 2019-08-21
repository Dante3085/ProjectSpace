#pragma once

#include <string>

class Logable
{
public:
	virtual std::string toString() const = 0;
};