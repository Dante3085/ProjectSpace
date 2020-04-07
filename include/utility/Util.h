
#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "collision/Line2F.h"
#include "scenes/Scene.h"

namespace ProjectSpace
{
	// Forward declarations

	// sf::Vector2<T>

	// For printing sf::Vector2<T> to std::cout
	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> const& v)
	{
		return stream << "{ " << v.x << ", " << v.y << " }";
	}

	// Get std::string representation of sf::Vector2<T>
	template <class T>
	std::string toString(sf::Vector2<T> const& v)
	{
		return "{ " += std::to_string(v.x) += ", " += std::to_string(v.y) += " }";
	}

	// Create a copy of v1 and divide every coordinate by the corresponding coordinate in v2
	template <class T>
	sf::Vector2<T> operator/(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2)
	{
		return sf::Vector2<T>{ v1.x / v2.x, v1.y / v2.y };
	}

	// Create a copy of v and add scalar to every coordinate
	template <class T, class U>
	sf::Vector2<T> operator+(sf::Vector2<T> const& v, U scalar)
	{
		return sf::Vector2<T>{ v.x + scalar, v.y + scalar };
	}

	// Create a copy of v and subtract scalar from every coordinate
	template <class T>
	sf::Vector2<T> operator-(sf::Vector2<T> const& v, float scalar)
	{
		return sf::Vector2<T>{ v.x - scalar, v.y - scalar };
	}

	// Get the length of v
	template <class T>
	T vectorLength(sf::Vector2<T> const& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	// Get the scalarProduct of v1 and v2
	template <class T>
	float scalarProduct(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	// Create a copy of v and normalize it
	template <class T>
	sf::Vector2<T> normalizedVector(sf::Vector2<T> const& v)
	{
		return v / vectorLength(v);
	}

	// For printing r to std::cout
	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Rect<T> const& r)
	{
		return stream << "{ " << r.left << ", " << r.top << ", " << r.width << ", " << r.height << " }";
	}

	// For printing every element of v to std::cout
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

	template <class K, class V>
	std::ostream& operator<<(std::ostream& stream, std::map<K, V>& map)
	{
		stream << "{ ";
		for (auto& pair : map)
		{
			stream << "(" << pair.first << ", " << pair.second << ")";
		}
		return stream << "}";
	}

	void debugSfString(sf::String const& sfString);

	// Inserts \n into text according to given lineLength, so that text wraps in between words.
	void addLineWrapping(sf::String& text, int lineLength);
	std::vector<sf::String> addTextWrapping(sf::String const& original, int lineLength, float textHeight, float lineHeight);

	namespace DebugDrawing
	{
		// TODO: A way to remove these as well.
		void drawPoint(sf::Vector2f const& point, Scene& scene);
		void drawLine(sf::Vector2f const& begin, sf::Vector2f const& end, Scene& scene);
		void drawRec(sf::Vector2f const& position, sf::Vector2f const& size, sf::Color const& color, Scene& scene);
		void drawFloatRect(sf::FloatRect const& floatRect, Scene& scene);
	}
	namespace dd = DebugDrawing;
}

#endif