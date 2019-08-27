
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <vector>

#include "Line2F.h"

namespace ProjectSpace
{
	std::ostream& operator<<(std::ostream& stream, sf::Vector2f const& v);
	std::ostream& operator<<(std::ostream& stream, sf::FloatRect const& r);
	float vectorLength(sf::Vector2f const& v);
	sf::Vector2f vectorMultScalar(sf::Vector2f const& v, float scalar);
	sf::Vector2f operator*(sf::Vector2f const& v, float scalar);
	sf::Vector2f operator-(sf::Vector2f const& v1, sf::Vector2f v2);
	float scalarProduct(sf::Vector2f const& v1, sf::Vector2f const& v2);
	sf::Vector2f normalizedVector(sf::Vector2f const& v);

	template <class T>
	std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> v);
	
	template <class T>
	std::ostream& operator<<(std::ostream& stream, std::vector<T> v);
}

#endif