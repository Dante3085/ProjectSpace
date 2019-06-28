#include "LayerCollidable.h"

namespace ProjectSpace
{
	LayerCollidable::LayerCollidable(sf::Vector2f position, sf::Vector2f size,
		std::vector<sf::Vector2f> points)
		: cb{position, size}, cs{points}
	{
	}

	bool LayerCollidable::collidesWith(Collidable const* partner)
	{
		if (cb.collidesWith(partner))
		{
			cb.setOutlineColor(sf::Color{ 255, 0, 0 });
			if (cs.collidesWith(partner))
			{
				return true;
			}
		}
		else
		{
			cb.setOutlineColor(sf::Color{ 0, 0, 255 });
			return false;
		}
	}

	sf::FloatRect LayerCollidable::getGlobalBounds() const
	{
		return sf::FloatRect();
	}

	sf::Shape const& LayerCollidable::getShape() const
	{
		// TODO: insert return statement here
		return sf::RectangleShape();
	}

	void LayerCollidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(cb);
		target.draw(cs);
	}

	void LayerCollidable::move(sf::Vector2f const& v)
	{
		cb.move(v);
		cs.move(v);
	}

	void LayerCollidable::setPosition(sf::Vector2f const& v)
	{
		cb.setPosition(v);
		cs.setPosition(v);
	}

	void LayerCollidable::setOulineThickness(float thickness)
	{
		cb.setOutlineThickness(thickness);
		cs.setOutlineThickness(thickness);
	}

	void LayerCollidable::setFillColor(sf::Color const& color)
	{
		cb.setFillColor(color);
		cs.setFillColor(color);
	}

	void LayerCollidable::setOutlineColor(sf::Color const& color)
	{
		cb.setOutlineColor(color);
		cs.setOutlineColor(color);
	}
}
