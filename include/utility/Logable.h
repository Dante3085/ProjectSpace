
#ifndef LOGABLE_H
#define LOGABLE_H

#include <string>

class Logable
{
public:
	virtual std::string toString() const = 0;
};

#endif