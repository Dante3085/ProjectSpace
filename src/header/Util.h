
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

#include "Line2F.h"

namespace ProjectSpace
{
	static std::ostream& operator<<(std::ostream& stream, sf::Vector2f const& v)
	{
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}

	static std::ostream& operator<<(std::ostream& stream, sf::FloatRect const& r)
	{
		stream << "{{" << r.left << ", " << r.top << "}, {" << r.left + r.width << ", " << r.top <<"}, {"
		<< r.left + r.width << ", " << r.top + r.height << "}, {" << r.left << ", " << r.top + r.height << "}}";
		return stream;
	}

	static float vectorLength(sf::Vector2f const& v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}
}

#endif