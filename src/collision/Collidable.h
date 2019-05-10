
#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <vector>
#include <functional>

#include "CollisionType.h"
#include "Line2F.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class that gives inheriting classes the function to detect and handle collisions between each other.
	 */
	class Collidable
	{
	public:

		/**
		 * @brief      Constructs a Collidable with the given CollisionType.
		 *
		 * @param[in]  type  The type
		 */
		Collidable(CollisionType type = CollisionType::NONE);

		/**
		 * @brief      Virtual destructor for inheriting classes.
		 */
		virtual ~Collidable();

		/**
		 * @brief      Returns whether or not the given Collidable collides with this Collidable.
		 *
		 * @param      partner  The other collidable with which the collision is to be tested.
		 *
		 * @return     true if the given Collidable collides with this Collidable, otherwise false.
		 */
		virtual bool collidesWith(Collidable const* partner) const = 0;

		/**
		 * @brief      Behaviour of this Collidable upon colliding with the given Collidable.
		 *
		 * @param      partner  The other Collidable with which this Collidalbe collided.
		 */
		void handleCollision(Collidable* partner);

		/**
		 * @brief      Gets the global bounds of this Collidable.
		 *
		 * @return     The global bounds of this Collidable.
		 */
		virtual sf::FloatRect getGlobalBounds() const = 0;

		/**
		 * @brief      Gets the shape of this Collidable.
		 *
		 * @return     The shape of this Collidable.
		 */
		virtual sf::Shape const& getShape() const = 0;

		/**
		 * @brief      Gets the lines of this Collidable. A Collidable is a 2D-Polygon with n edges that 
		 * 			   can be described as n lines.
		 *
		 * @return     The lines of this Collidable.
		 */
		std::vector<Line2F*> const& getLines() const;

		/**
		 * @brief      Gets whether or not the Collidable draws it's BoundingBox.
		 *
		 * @return     True if the Collidable draws it's BoundingBox, otherwise false.
		 */
		bool getDrawBoundingBox();

		/**
		 * @brief      Sets the whether or not the Collidable should draw it's BoundingBox.
		 *
		 * @param[in]  drawBoundingBox  The draw bounding box
		 */
		void setDrawBoundingBox(bool drawBoundingBox);

		/**
		 * @brief      Gets the CollisionType of this Collidable.
		 *
		 * @return     The CollisionType of this Collidable.
		 */
		CollisionType getCollisionType();

		/**
		 * @brief      Sets the CollisionType.
		 *
		 * @param[in]  type  The CollisionType.
		 */
		void setCollisionType(CollisionType type);

		/**
		 * @brief      Sets the collision handler of this Collidable.
		 *
		 * @param[in]  collisionHandler  The collision handler
		 */
		void setCollisionHandler(std::function<void(Collidable* partner)> collisionHandler);

	protected:
		CollisionType type;				// The CollisionType of this Collidable.
		bool drawBoundingBox;			// Stores if this Collidable draws it's BoundingBox.
		std::vector<Line2F*> lines;		// The lines that make up this Collidable.
		std::function<void(Collidable* partner)> collisionHandler; // Behaviour for when this Collidable collides with another Collidable.
	};
}

#endif