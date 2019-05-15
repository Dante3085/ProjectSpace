
#include "Line2F.h"
#include "Util.h"
#include <math.h>

namespace ProjectSpace
{
	Line2F::Line2F(sf::Vector2f p1, sf::Vector2f p2)
	: positionVector{p1}, p2{p2}, directionVector{p2 - p1} {}

	sf::Vector2f Line2F::point(float parameter) const
	{
		return positionVector + (parameter * directionVector);
	}

	void Line2F::create(sf::Vector2f p1, sf::Vector2f p2)
	{
		positionVector = p1;
		directionVector = p2 - p1;
	}

	bool Line2F::intersects(Line2F const& l2) const
	{
		// v1: Parameter dieser Gerade. v2 Parameter von l2.
		float v1 = 0, v2 = 0;

		if (directionVector.x == 0)
		{
			v2 = (positionVector.x - l2.positionVector.x) / l2.directionVector.x;
			v1 = (l2.positionVector.y + (l2.directionVector.y * v2) - positionVector.y) / directionVector.y; 
		}
		else
		{
			v2 = ((positionVector.y - ((positionVector.x * directionVector.y) / directionVector.x)) - (l2.positionVector.y - ((l2.positionVector.x * directionVector.y) / directionVector.x)))
			/ (l2.directionVector.y - ((l2.directionVector.x * directionVector.y) / directionVector.x));

			v1 = (l2.positionVector.x + (l2.directionVector.x * v2) - positionVector.x) / directionVector.x;
		}
		
		// Soll Rechnungen abfangen, wie "irgendwas / 0", bei denen sowieso keine Kollision bei rumkommen würde.
		// Warum dies dann immer funktioniert, ist mir selbst nicht ganz klar, da ich nicht völlig durchdacht habe wohin dieses
		// Verfahren bei jeder Möglichkeit führt.
		if (isinf(v1) || isinf(v2)
			|| isnan(v1) || isnan(v2))
		{
			return false;
		}

		/*std::cout << intersection << ", " << intersection2 << std::endl;
		std::cout << "v1: " << v1 << ", v2: " << v2 << std::endl;
		std::cout << "this Line2F: " << *this << ", l2: " << l2 << std::endl << "------------------" << std::endl;*/

		// Sind v1, v2 kleiner 0 bzw. groesser 1, produzieren sie einen Schnittpunkt außerhalb der Punktgrenzen der beiden Geraden.
		// Für uns also keinen Schnittpunkt.
		if (v1 < 0 || v1 > 1 || v2 < 0 || v2 > 1)
		{
			return false;
		}
		return true;
	}

	std::ostream& operator<<(std::ostream& stream, Line2F const& l)
	{
		stream << "{" << l.positionVector << ", " << l.p2 << "}";
		return stream;
	}
}