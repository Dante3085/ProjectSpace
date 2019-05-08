
#include "CollisionShape.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace ProjectSpace
{
	CollisionShape::CollisionShape(std::vector<sf::Vector2f> points)
	: shape{points.size()}
	{
			// Uebergebene Points in die ConvexShape setzen.
		for (int i = 0; i < points.size(); ++i)
		{
			shape.setPoint(i, points[i]);
		}

			// ConvexShape visuell anpassen.
		shape.setOutlineThickness(2);
		shape.setOutlineColor(sf::Color{30,144,255});
		shape.setFillColor(sf::Color{0, 0, 0, 0});

			// Linien der ConvexShape erstellen und abspeichern.

			// 2 Punkte => eine Line. 1 oder keine Punkte => Keine Linie
		if (points.size() == 2)
		{
			lines.push_back(new Line2F{points[0], points[1]});
		}

		else if (points.size() > 2)
		{
			for (int i = 0; i < points.size() - 1; ++i)
			{
				lines.push_back(new Line2F{points[i], points[i + 1]});
			}
				// Ziehe zuletzt noch Linie vom letzten zum ersten Punkt.
			lines.push_back(new Line2F{points[points.size() - 1], points[0]});
		}

			// obige lines korrekt.
	}

	bool CollisionShape::collidesWith(Collidable const* partner) const
	{
		for (Line2F* l1 : this->lines)
		{
			for (Line2F* l2 : partner->getLines())
			{
				if (l1->intersects(*l2))
				{
					return true;
				}
			}
		}
		return false;
	}

	void CollisionShape::handleCollision(Collidable* partner)
	{

	}

	sf::FloatRect CollisionShape::getGlobalBounds() const
	{
		return shape.getGlobalBounds();
	}

	void CollisionShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (drawBoundingBox)
		{
			/*sf::FloatRect globalBounds = shape.getGlobalBounds();

			sf::RectangleShape boundingBox{sf::Vector2f{globalBounds.width, globalBounds.height}};
			boundingBox.setPosition(sf::Vector2f{globalBounds.left, globalBounds.top});
			boundingBox.setOutlineThickness(1);
			boundingBox.setOutlineColor(sf::Color{30,144,255});
			boundingBox.setFillColor(sf::Color{0, 0, 0, 0});*/
			// target.draw(boundingBox);
		}
		target.draw(shape);
	}

	sf::Shape const& CollisionShape::getShape() const
	{
		return shape;
	}
}