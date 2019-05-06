
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

#include "Collidable.h"

namespace ProjectSpace
{
	class CollisionBox : public Collidable, public sf::Drawable
	{
	public:
		CollisionBox(sf::Vector2f size = sf::Vector2f{50, 50}, sf::Vector2f position = sf::Vector2f{0, 0});

		bool collidesWith(Collidable const* partner) const;
		void handleCollision(Collidable* partner);
		sf::FloatRect getGlobalBounds() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Shape const& getShape() const override;

	private:
		sf::RectangleShape box;
	};
}

#endif