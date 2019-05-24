
#include "Collidable.h"

namespace ProjectSpace
{
	Collidable::Collidable(CollisionType type) 
	: type{ type }, drawBoundingBox{ true }, collisionHandler{ [](Collidable* partner){} } 
	{

	}

	Collidable::~Collidable() 
	{
		for (Line2F* l : lines)
		{
			delete l;
		}
	}

	void Collidable::handleCollision(Collidable* partner)
	{
		collisionHandler(partner);
	}

	std::vector<Line2F*> const& Collidable::getLines() const
	{
		return lines;
	}

	bool Collidable::getDrawBoundingBox()
	{
		return drawBoundingBox;
	}

	void Collidable::setDrawBoundingBox(bool drawBoundingBox)
	{
		this->drawBoundingBox = drawBoundingBox;
	}

	CollisionType Collidable::getCollisionType()
	{
		return type;
	}

	void Collidable::setCollisionType(CollisionType type)
	{
		this->type = type;
	}

	void Collidable::setCollisionHandler(std::function<void(Collidable* partner)> collisionHandler)
	{
		this->collisionHandler = collisionHandler;
	}
}