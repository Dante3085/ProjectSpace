
#include "collision/Line2D.h"

namespace ProjectSpace
{
	Line2D::Line2D(float gradient, float yAxis) : gradient{gradient}, yAxis{yAxis}, pointsGiven{false} {}

	Line2D::Line2D(sf::Vector2f p1, sf::Vector2f p2)
		: p1{p1}, 
		p2{p2}, 
		gradient{(p2.y - p1.y) / (p2.x - p1.x)}, 
		yAxis{p1.y + (-(p1.x * gradient))}, 
		pointsGiven{true} {}


		/**
		 * @brief      Zur nachtraeglichen Aenderung der Line2D.
		 *
		 * @param[in]  p1    First Point
		 * @param[in]  p2    Second Point
		 */
	void Line2D::create(sf::Vector2f p1, sf::Vector2f p2)
	{
		this->p1 = p1;
		this->p2 = p2;

		gradient = (p2.y - p1.y) / (p2.x - p1.x);
		yAxis = p1.y + (-(p1.x * gradient));
	}

	sf::Vector2f Line2D::f(float x) const
	{
		return sf::Vector2f{x, (gradient * x) + yAxis};
	}

	bool Line2D::intersects(Line2D const* line, bool betweenPoints)
	{
		sf::Vector2f intersection;
		intersection.x = (line->yAxis + (-(yAxis))) / (gradient + (-(line->gradient)));
		intersection.y = (gradient * intersection.x) + yAxis;

			// Probe, ob beide Lines denselben y-Wert herausbekommen.
		if (intersection.y != line->f(intersection.x).y)
		{
			return false;
		}

			// Wenn Punkte gegeben wurden und es erwuenscht ist, pruefen, ob errechneter Schnittpunkt
			// zwischen den gegebenen Punkten liegt.
		if (betweenPoints && pointsGiven && line->getPointsGiven())
		{			
				// Liegt Schnittpunkt zwischen Punkten dieser Line2D.
			if (intersection.x < p1.x
				|| intersection.x > p2.x
				|| intersection.y < p1.y
				|| intersection.y > p2.y)
			{
				return false;
			}

				// Liegt Schnittpunkt zwischen Punkten der uebergebenden Line2D
			if (intersection.x < line->p1.x
				|| intersection.x > line->p2.x
				|| intersection.y < line->p1.y
				|| intersection.y > line->p2.y)
			{
				return false;
			}
		}
		return true;
	}

	sf::Vector2f Line2D::calcIntersection(Line2D const* line, bool betweenPoints)
	{
		sf::Vector2f intersection;
		intersection.x = (line->yAxis + (-(yAxis))) / (gradient + (-(line->gradient)));
		intersection.y = (gradient * intersection.x) + yAxis;

			// Probe, ob beide Lines denselben y-Wert herausbekommen.
		if (intersection.y != line->f(intersection.x).y)
		{
			std::cout << "@Line2D::calcIntersection(): No Intersection!" << std::endl;
			return sf::Vector2f{-1, -1};
		}

			// Wenn Punkte gegeben wurden und es erwuenscht ist, pruefen, ob errechneter Schnittpunkt
			// zwischen den gegebenen Punkten liegt.
		if (betweenPoints && pointsGiven && line->getPointsGiven())
		{			
				// Liegt Schnittpunkt zwischen Punkten dieser Line2D.
			if (intersection.x < p1.x
				|| intersection.x > p2.x
				|| intersection.y < p1.y
				|| intersection.y > p2.y)
			{
				std::cout << "@Line2D::calcIntersection(): No Intersection!" << std::endl;
				return sf::Vector2f{-1, -1};
			}

				// Liegt Schnittpunkt zwischen Punkten der uebergebenden Line2D
			if (intersection.x < line->p1.x
				|| intersection.x > line->p2.x
				|| intersection.y < line->p1.y
				|| intersection.y > line->p2.y)
			{
				std::cout << "@Line2D::calcIntersection(): No Intersection!" << std::endl;
				return sf::Vector2f{-1, -1};
			}
		}
		return intersection;
	}

	float Line2D::getGradient()
	{
		return gradient;
	}

	void Line2D::setGradient(float gradient)
	{
		this->gradient = gradient;
	}

	float Line2D::getYAxis()
	{
		return yAxis;
	}

	void Line2D::setYAxis(float yAxis)
	{
		this->yAxis = yAxis;
	}

	bool Line2D::getPointsGiven() const
	{
		return pointsGiven;
	}

	std::ostream& operator<<(std::ostream& stream, Line2D const& line)
	{
		stream << "y = " << line.gradient << "x + " << line.yAxis;
		return stream;
	}

	sf::Vector2f Line2D::getP1()
	{
		return p1;
	}

	sf::Vector2f Line2D::getP2()
	{
		return p2;
	}
}