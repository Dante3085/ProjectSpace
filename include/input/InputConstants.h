
#ifndef INPUT_CONSTANTS_H
#define INPUT_CONSTANTS_H

namespace ProjectSpace
{
	enum class Action
	{
		LIST_UP,
		LIST_DOWN,
		LIST_SELECT,
	};

	enum class State
	{
		LIST_HOLD_UP,
		LIST_HOLD_DOWN,

		WALK_NORTH,
		WALK_EAST,
		WALK_SOUTH,
		WALK_WEST,
	};
}

#endif