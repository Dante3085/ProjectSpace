
#ifndef WINDOW_STYLE_H
#define WINDOW_STYLE_H

namespace ProjectSpace
{
	enum class WindowStyle
	{
		NONE = 0,
		TITLEBAR = 1 << 0,
		RESIZE = 1 << 1,
		CLOSE = 1 << 2,
		FULLSCREEN = 1 << 3,
		DEFAULT = TITLEBAR | RESIZE | CLOSE,
	};
}

#endif