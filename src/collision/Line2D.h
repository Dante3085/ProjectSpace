
#ifndef LINE_2D_H
#define LINE_2D_H

#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "../Util.h"

namespace ProjectSpace
{
	class Line2D
	{
	public:
		Line2D(float gradient, float yAxis);
		Line2D(sf::Vector2f p1, sf::Vector2f p2);

		/**
		 * @brief      Zur nachtraeglichen Aenderung der Line2D.
		 *
		 * @param[in]  p1    First Point
		 * @param[in]  p2    Second Point
		 */
		void create(sf::Vector2f p1, sf::Vector2f p2);
		sf::Vector2f f(float x) const;
		bool intersects(Line2D const* line, bool betweenPoints = false);
		sf::Vector2f calcIntersection(Line2D const* line, bool betweenPoints = false);
		float getGradient();
		void setGradient(float gradient);
		float getYAxis();
		void setYAxis(float yAxis);
		bool getPointsGiven() const;
		friend std::ostream& operator<<(std::ostream& stream, Line2D const& line);
		sf::Vector2f getP1();
		sf::Vector2f getP2();

	private:
		float gradient; // Steigung
		float yAxis;   // y-Achsenabschnitt
		sf::Vector2f p1;
		sf::Vector2f p2;
		bool pointsGiven;
	};
}

#endif