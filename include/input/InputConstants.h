
#ifndef INPUT_CONSTANTS_H
#define INPUT_CONSTANTS_H

namespace ProjectSpace
{
	enum class Action
	{
		LIST_UP,
		LIST_DOWN,
		LIST_SELECT,
		PRINT
	};

	enum class State
	{
		WALK_NORTH,
		WALK_EAST,
		WALK_SOUTH,
		WALK_WEST
	};
}

#endif