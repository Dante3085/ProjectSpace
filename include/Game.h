
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>
#include <map>

#include "scenes/Entity.h"
#include "scenes/EScene.h"
#include "scenes/Scene.h"
#include "WindowStyle.h"

namespace ProjectSpace
{
	/**
	 * @brief      Core class of the Game. Contains main Game-Loop and Event-Loop.
	 */
	class Game
	{
	public:

		/**
		 * @brief      Constructs a Game detecting the monitor's resolution automatically.
		 *
		 * @param[in]  windowTitle  Title of the Game's window.
		 */
		Game(std::string const& windowTitle, WindowStyle style = DEFAULT);

		/**
		 * @brief      Constructs a Game.
		 *
		 * @param[in]  screenWidth   Width of the Game's window.
		 * @param[in]  screenHeight  Height of the Game's window.
		 * @param[in]  windowTitle   Title of the Game's window.
		 */
		Game(std::string const& windowTitle, unsigned int screenWidth, unsigned int screenHeight, WindowStyle style = DEFAULT);

		/**
		 * @brief      Destroys every Scene of the Game.
		 */
		~Game();

		/**
		 * @brief      Starts the Game/Game-Loop.
		 */
		void start();

		/**
		 * @brief      Sets the current scene.
		 *
		 * @param[in]  scene  The scene
		 */
		void setCurrentScene(EScene scene);

	private:
		/**
		 * @brief      Helper function for initializing everything before starting the Game. Creates all Sprites and stuff...
		 */
		void init();

		sf::RenderWindow window; 		 // Window of the Game.
		std::map<EScene, Scene*> scenes; // All Scenes of the Game.
		Scene* currentScene; 			 // Scene that is currently active (is drawn and updated).
		float windowWidth;
		float windowHeight;

		std::vector<Entity*> globalEntities; 		// Entities that get updated independent of any specific Scene.
		std::vector<sf::Drawable*> globalDrawables;	// sf::Drawables that get drawn independent of any specific Scene.

		bool freeze;
		bool f2LastFrame;
	};
}

#endif