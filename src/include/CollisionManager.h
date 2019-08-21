
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SFML/System/Time.hpp>
#include <vector>

#include "Entity.h"
#include "Collidable.h"
#include "Log.h"

namespace ProjectSpace
{
	class CollisionManager : public Entity
	{
	public:
		CollisionManager(std::vector<Collidable*> collidables);

		void update(sf::Time time) override;

	private:
		std::vector<Collidable*> collidables;
	};
}

#endif