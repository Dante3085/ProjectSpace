
#include "collision/CollisionBox.h"

namespace ProjectSpace
{
	CollisionBox::CollisionBox(sf::Vector2f position, sf::Vector2f size)
		: box{size}
	{
			// Position und Aussehen der CollisionBox festlegen.
		box.setPosition(position);
		box.setOutlineThickness(2);
		box.setOutlineColor(sf::Color{30,144,255});
		box.setFillColor(sf::Color{0, 0, 0, 0});

			// Linien der CollisionBox abspeichern.
		sf::Vector2f upperLeft{ position.x, position.y };
		sf::Vector2f upperRight{position.x + size.x, position.y};
		sf::Vector2f lowerRight{ position.x + size.x, position.y + size.y };
		sf::Vector2f lowerLeft{position.x, position.y + size.y};

		lines.push_back(new Line2F{upperLeft, upperRight});
		lines.push_back(new Line2F{upperRight, lowerRight});
		lines.push_back(new Line2F{lowerRight, lowerLeft});
		lines.push_back(new Line2F{lowerLeft, upperLeft});
	}

	bool CollisionBox::collidesWith(Collidable const* partner)
	{
		// return box.getGlobalBounds().intersects(partner->getGlobalBounds());

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

	void CollisionBox::move(sf::Vector2f const& v)
	{
		box.move(v);

		sf::FloatRect bounds = box.getGlobalBounds();

		sf::Vector2f upperLeft{ bounds.left, bounds.top };
		sf::Vector2f upperRight{ bounds.left + bounds.width, bounds.top };
		sf::Vector2f lowerRight{ bounds.left + bounds.width, bounds.top + bounds.height };
		sf::Vector2f lowerLeft{ bounds.left, bounds.top + bounds.height };

		lines[0]->create(upperLeft, upperRight);
		lines[1]->create(upperRight, lowerRight);
		lines[2]->create(lowerRight, lowerLeft);
		lines[3]->create(lowerLeft, upperLeft);
	}

	void CollisionBox::setPosition(sf::Vector2f const& v)
	{
		box.setPosition(v);

		sf::FloatRect bounds = box.getGlobalBounds();

		sf::Vector2f upperLeft{ bounds.left, bounds.top };
		sf::Vector2f upperRight{ bounds.left + bounds.width, bounds.top };
		sf::Vector2f lowerRight{ bounds.left + bounds.width, bounds.top + bounds.height };
		sf::Vector2f lowerLeft{ bounds.left, bounds.top + bounds.height };

		lines[0]->create(upperLeft, upperRight);
		lines[1]->create(upperRight, lowerRight);
		lines[2]->create(lowerRight, lowerLeft);
		lines[3]->create(lowerLeft, upperLeft);
	}

	void CollisionBox::setOutlineThickness(float thickness)
	{
		box.setOutlineThickness(thickness);
	}

	void CollisionBox::setFillColor(sf::Color const& color)
	{
		box.setFillColor(color);
	}

	void CollisionBox::setOutlineColor(sf::Color const& color)
	{
		box.setOutlineColor(color);
	}
}