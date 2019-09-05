
#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "collision/Line2F.h"
#include "scenes/Scene.h"

namespace ProjectSpace
{
	// sf::Vector2<T>
	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> const& v)
	{
		return stream << "{ " << v.x << ", " << v.y << " }";
	}

	template <class T>
	std::string toString(sf::Vector2<T> const& v)
	{
		return "{ " += std::to_string(v.x) += ", " += std::to_string(v.y) += " }";
	}

	template <class T>
	sf::Vector2<T> operator/(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2)
	{
		return sf::Vector2<T>{ v1.x / v2.x, v1.y / v2.y };
	}

	template <class T, class U>
	sf::Vector2<T> operator+(sf::Vector2<T> const& v, U scalar)
	{
		return sf::Vector2<T>{ v.x + scalar, v.y + scalar };
	}

	template <class T>
	sf::Vector2<T> operator-(sf::Vector2<T> const& v, float scalar)
	{
		return sf::Vector2<T>{ v.x - scalar, v.y - scalar };
	}

	template <class T>
	T vectorLength(sf::Vector2<T> const& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	template <class T>
	float scalarProduct(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <class T>
	sf::Vector2<T> normalizedVector(sf::Vector2<T> const& v)
	{
		return v / vectorLength(v);
	}

	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Rect<T> const& r)
	{
		return stream << "{ " << r.left << ", " << r.top << ", " << r.width << ", " << r.height << " }";
	}

	template <class T>
	std::ostream& operator<<(std::ostream& stream, std::vector<T> v)
	{
		stream << "{ ";
		for (T const& t : v)
		{
			stream << t << " ";
		}
		stream << "}";
	}

	// Inserts \n into text according to given lineLength, so that text wraps in between words.
	void addLineWrapping(sf::String& text, int lineLength);

	namespace DebugDrawing
	{
		// TODO: A way to remove these as well.
		void drawLine(sf::Vector2f const& begin, sf::Vector2f const& end, Scene& scene);
		void drawRec(sf::Vector2f const& position, sf::Vector2f const& size, Scene& scene);
	}
	namespace dd = DebugDrawing;
}

#endif