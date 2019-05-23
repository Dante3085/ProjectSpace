#include "LayerCollidable.h"

namespace ProjectSpace
{
	LayerCollidable::LayerCollidable(sf::Vector2f position, sf::Vector2f size,
		std::vector<sf::Vector2f> points)
		: cb{position, size}, cs{points}
	{

	}

	bool LayerCollidable::collidesWith(Collidable const* partner) const
	{
		return cb.collidesWith(partner) ? cs.collidesWith(partner) : false;
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
}
