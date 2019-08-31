
#ifndef SAT_H
#define SAT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <vector>

namespace ProjectSpace
{
	// Separating Axis Theorem
	namespace SAT
	{
		class Projection
		{
		public:
			Projection(float min, float max) : min{min}, max{max} {}

			bool overlaps(Projection const& p2)
			{
				return p2.max >= min && p2.min <= max;
			}

			float min;
			float max;
		};

		/**
		 * @brief      Returns perpendicular(senkrecht) vector.
		 *
		 * @param[in]  v     { parameter_description }
		 *
		 * @return     { description_of_the_return_value }
		 */
		sf::Vector2f perp(sf::Vector2f const& v)
		{
			return sf::Vector2f{-v.y, v.x};
		}

		float dotProduct(sf::Vector2f const& v1, sf::Vector2f const& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		std::vector<sf::Vector2f> getAxes(sf::Shape const& shape)
		{
			std::vector<sf::Vector2f> axes;
			int shapePointCount = shape.getPointCount();

			for (int i = 0; i < shapePointCount; ++i)
			{
				sf::Vector2f p1 = shape.getPoint(i); 									// current vertex
				sf::Vector2f p2 = shape.getPoint((i + 1) == shapePointCount ? 0 : (i + 1)); // next vertex
				sf::Vector2f edge = p1 - p2; 											// subract the two to get edge vector
				sf::Vector2f normal = perp(edge);
				axes.push_back(normal);
			}
			return axes;
		}

		Projection project(sf::Shape const& shape, sf::Vector2f const& axis)
		{
			float min = dotProduct(axis, shape.getPoint(0));
			float max = min;

			for (int i = 0; i < shape.getPointCount(); ++i)
			{
				// must be normalized axis.
				float p = dotProduct(axis, shape.getPoint(i));

				if (p < min)
				{
					min = p;
				}
				else if (p > max)
				{
					max = p;
				}
			}
			return Projection{min, max};
		}

		bool collide(sf::Shape const& s1, sf::Shape const& s2)
		{
			std::vector<sf::Vector2f> axes1 = getAxes(s1);
			std::vector<sf::Vector2f> axes2 = getAxes(s2);

			for (int i = 0; i < axes1.size(); ++i)
			{
				sf::Vector2f axis = axes1[i];

				Projection p1 = project(s1, axis);
				Projection p2 = project(s2, axis);

				if (!p1.overlaps(p2))
				{
					return false;
				}
			}

			for (int i = 0; i < axes2.size(); ++i)
			{
				sf::Vector2f axis = axes2[i];

				Projection p1 = project(s1, axis);
				Projection p2 = project(s2, axis);

				if (!p1.overlaps(p2))
				{
					return false;
				}
			}
			return true;
		}
	}
}

#endif 