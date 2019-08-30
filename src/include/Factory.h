
#ifndef FACTORY_H
#define FACTORY_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Scene.h"
#include "ExpandMenu.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class only with static functions for creating concrete Scenes/Levels, etc.
	 */
	class Factory
	{
	public:

		// NOTE(moritz): Die folgenden Funktionen sind erstmal nur dafuer da den ganzen Code zum Testen zu halten.
		static Scene* create_debug_scene(sf::RenderWindow& window);
		static Scene* create_empty_scene(sf::RenderWindow& window);
		static Scene* create_tilemap_scene(sf::RenderWindow& window);
		static Scene* create_collision_scene(sf::RenderWindow& window);
		static Scene* create_menu_scene(sf::RenderWindow& window);

	private:
		Factory() {}
	};
}

#endif