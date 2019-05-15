
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
		static Scene* createDebugScene(sf::RenderWindow& window);
		static Scene* createEmptyScene(sf::RenderWindow& window);
		static Scene* createTilemapScene(sf::RenderWindow& window);

		static ExpandMenu* createCombatMenu();

	private:
		Factory() {}
	};
}

#endif