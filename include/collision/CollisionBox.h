
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Collidable.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for creating Boxes that act as collision objects in the world.
	 */
	class CollisionBox : public Collidable, public sf::Drawable
	{
	public:

		/**
		 * @brief      Constructs a CollisionBox with the given size at the given Position.
		 *
		 * @param[in]  size      The size
		 * @param[in]  position  The position
		 */
		CollisionBox(sf::Vector2f position = sf::Vector2f{0, 0}, sf::Vector2f size = sf::Vector2f{50, 50});

		/**
		 * @brief      Returns whether or not this CollisionBox collides with the given Collidable.
		 *
		 * @param      partner  The Collidable with which the collision is to be tested.
		 *
		 * @return     True if this CollisionBox collides with the given Collidable, otherwise false.
		 */
		bool collidesWith(Collidable const* partner) override;

		/**
		 * @brief      Behaviour of this CollisionBox upon colliding with the given Collidable.
		 *
		 * @param      partner  The Collidable with which this Collidalbe collided.
		 */
		void handleCollision(Collidable* partner);
		sf::FloatRect getGlobalBounds() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Shape const& getShape() const override;

		void move(sf::Vector2f const& v);
		void setPosition(sf::Vector2f const& v);

		void setOutlineThickness(float thickness);
		void setFillColor(sf::Color const& color);
		void setOutlineColor(sf::Color const& color);

	private:
		sf::RectangleShape box;
	};
}

#endif