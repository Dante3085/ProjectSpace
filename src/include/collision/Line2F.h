
#ifndef LINE2F_H
#define LINE2F_H

#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace ProjectSpace
{
	class Line2F
	{
	public:
		Line2F(sf::Vector2f p1, sf::Vector2f p2);

		sf::Vector2f point(float parameter) const;
		void create(sf::Vector2f p1, sf::Vector2f p2);
		bool intersects(Line2F const& line2) const;

		friend std::ostream& operator<<(std::ostream& stream, Line2F const& l);

	private:
		sf::Vector2f positionVector;  // Ortsvektor (Erster Punkt)
		sf::Vector2f directionVector; // Richtungsvektor
		sf::Vector2f p2;			  // Zweiter Punkt
	};
}

#endif