
#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <vector>

#include "CollisionType.h"
#include "Line2F.h"

namespace ProjectSpace
{
	class Collidable
	{
	public:
		Collidable(CollisionType type = CollisionType::NONE);
		virtual ~Collidable();

		virtual bool collidesWith(Collidable const* partner) const = 0;
		virtual void handleCollision(Collidable* partner) = 0;
		virtual sf::FloatRect getGlobalBounds() const = 0;
		virtual sf::Shape const& getShape() const = 0;

		std::vector<Line2F*> getLines() const;
		bool getDrawBoundingBox();
		void setDrawBoundingBox(bool drawBoundingBox);
		CollisionType getCollisionType();
		void setCollisionType(CollisionType type);

	protected:
		CollisionType type;
		bool drawBoundingBox;
		std::vector<Line2F*> lines;
	};
}

#endif