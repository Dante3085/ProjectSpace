
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Time.hpp>

namespace ProjectSpace
{
	/**
	 * @brief      Abstract representation of things that need to be updatet in the game.
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