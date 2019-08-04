
#include "CollisionManager.h"

namespace ProjectSpace
{
	CollisionManager::CollisionManager(std::vector<Collidable*> collidables) 
		: collidables{ collidables } {}

	void CollisionManager::update(sf::Time time)
	{
		for (Collidable* c1 : collidables)
		{
			for (Collidable* c2 : collidables)
			{
				if (c1 == c2)
				{
					continue;
				}
				else if (c1->collidesWith(c2))
				{
					c1->handleCollision(c2);
					c2->handleCollision(c1);
				}
			}
		}
	}
}