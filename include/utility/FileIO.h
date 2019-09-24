
#ifndef FILE_IO_H
#define FILE_IO_H

#include <istream>

namespace ProjectSpace
{
	// Returns read stream contents if successful, otherwise Logs an error message and
	// shuts down the program.
	template <class T>
	T attemptRead(std::istream& stream);
}

#endif