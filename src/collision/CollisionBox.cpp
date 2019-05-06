
#include "CollisionBox.h"

namespace ProjectSpace
{
	CollisionBox::CollisionBox(sf::Vector2f size, sf::Vector2f position)
	: box{size}
	{
			// Position und Aussehen der CollisionBox festlegen.
		box.setPosition(position);
		box.setOutlineThickness(2);
		box.setOutlineColor(sf::Color{30,144,255});
		box.setFillColor(sf::Color{0, 0, 0, 0});

			// Linien der CollisionBox abspeichern.
		sf::Vector2f upperRight{position.x + size.x, position.y};
		sf::Vector2f lowerLeft{position.x, position.y + size.y};
		sf::Vector2f lowerRight{position.x + size.x, position.y + size.y};

		lines.push_back(new Line2F{position, upperRight});
		lines.push_back(new Line2F{upperRight, lowerRight});
		lines.push_back(new Line2F{lowerRight, lowerLeft});
		lines.push_back(new Line2F{lowerLeft, position});
	}

	bool CollisionBox::collidesWith(Collidable const* partner) const
	{
		return box.getGlobalBounds().intersects(partner->getGlobalBounds());
	}

	void CollisionBox::handleCollision(Collidable* partner)
	{

	}

	sf::FloatRect CollisionBox::getGlobalBounds() const
	{
		return box.getGlobalBounds();
	}

	void CollisionBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (drawBoundingBox)
		{
			target.draw(box);
		}
	}

	sf::Shape const& CollisionBox::getShape() const
	{
		return box;
	}
}