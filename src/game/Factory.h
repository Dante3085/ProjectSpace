
#ifndef FACTORY_H
#define FACTORY_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Scene.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class only with static functions for creating concrete Scenes/Levels, etc.
	 */
	class Factory
	{
	public:

		// NOTE(moritz): Die folgenden Funktionen sind erstmal nur dafuer da den ganzen Code zum Testen zu halten.
		static Scene* CREATE_DEBUG_SCENE(sf::RenderWindow& window);
		static Scene* CREATE_DEBUG_SCENE_2(sf::RenderWindow& window);
		static Scene* CREATE_TILEMAP_SCENE(sf::RenderWindow& window);

	private:
		Factory() {}
	};
}

#endif