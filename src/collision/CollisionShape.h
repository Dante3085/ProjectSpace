
#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

#include "Collidable.h"
#include "../Util.h"

namespace ProjectSpace
{
	class CollisionShape : public Collidable, public sf::Drawable
	{
	public:
		CollisionShape(std::vector<sf::Vector2f> points);

		bool collidesWith(Collidable const* partner) const;
		void handleCollision(Collidable* partner);
		sf::FloatRect getGlobalBounds() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Shape const& getShape() const override;

	private:
		sf::ConvexShape shape;
	};
}

#endif