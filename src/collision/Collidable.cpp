
#include "Collidable.h"

namespace ProjectSpace
{
	Collidable::Collidable(CollisionType type) : type{type}, drawBoundingBox{false} {}

	Collidable::~Collidable() 
	{
		for (Line2F* l : lines)
		{
			delete l;
		}
	}

	std::vector<Line2F*> Collidable::getLines() const
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
}