
#include "utility/FileIO.h"

#include "utility/Log.h"

namespace ProjectSpace
{
	template <class T>
	T attemptRead(std::istream& stream)
	{
		T out;

		// "stream >> out" evaluates to a boolean expression that says if reading from stream
		// into out succeded.
		// The read terminates at whitespace characters by default.
		if (!(stream >> out))
		{
			Log::getInstance().defaultLog("Failed to read from given std::istream.", ll::ERR, true);
		}
		return out;
	}
}