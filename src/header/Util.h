
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

	static sf::Vector2f vectorMultScalar(sf::Vector2f const& v, float scalar)
	{
		return sf::Vector2f{ v.x * scalar, v.y * scalar };
	}

	static sf::Vector2f operator*(sf::Vector2f const& v, float scalar)
	{
		return sf::Vector2f{ v.x * scalar, v.y * scalar };
	}

	static sf::Vector2f operator-(sf::Vector2f const& v1, sf::Vector2f v2)
	{
		return sf::Vector2f{ v1.x - v2.x, v1.y - v2.y };
	}

	static float scalarProduct(sf::Vector2f const& v1, sf::Vector2f const& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	static sf::Vector2f normalizedVector(sf::Vector2f const& v)
	{
		return vectorMultScalar(v, 1.f / vectorLength(v));
	}

	template <class T>
	static std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> v)
	{
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}
}

#endif