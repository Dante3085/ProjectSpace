
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Time.hpp>

namespace ProjectSpace
{
	/**
	 * @brief      Represents a thing in the Game. Basically everything that needs updating every frame.
	 */
	class Entity
	{
	public:
		/**
		 * @brief      Virtual Destructor because other classes will inherit from Entity.
		 */
		virtual ~Entity() {}

		/**
		 * @brief      Updates the Entity.
		 *
		 * @param[in]  time  The time.
		 */
		virtual void update(sf::Time time) = 0;
	};
}

#endif