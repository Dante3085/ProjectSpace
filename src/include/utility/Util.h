
#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

#include "collision/Line2F.h"
#include "scenes/Scene.h"

namespace ProjectSpace
{
	std::ostream& operator<<(std::ostream& stream, sf::Vector2f const& v);
	std::ostream& operator<<(std::ostream& stream, sf::FloatRect const& r);
	float vectorLength(sf::Vector2f const& v);
	sf::Vector2f vectorMultScalar(sf::Vector2f const& v, float scalar);

	// Adds scalar to all of v's coordinates.
	sf::Vector2f operator+(sf::Vector2f const& v, float scalar);
	sf::Vector2f operator*(sf::Vector2f const& v, float scalar);
	sf::Vector2f operator-(sf::Vector2f const& v1, sf::Vector2f const& v2);
	sf::Vector2f operator/(sf::Vector2f const& v1, sf::Vector2f const& v2);
	float scalarProduct(sf::Vector2f const& v1, sf::Vector2f const& v2);
	sf::Vector2f normalizedVector(sf::Vector2f const& v);

	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> v);

	std::string toString(sf::Vector2f const& v);
	
	template <class T>
	std::ostream& operator<<(std::ostream& stream, std::vector<T> v);

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