
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>
#include <map>

#include "scenes/EScene.h"
#include "WindowStyle.h"
#include "input/InputManager.h"
#include "gui/FpsCounter.h"
#include "gui/Button.h"
#include "gui/ButtonMenu.h"
#include "gui/VBox.h"
#include "animation/TranslateAnimation.h"

namespace ProjectSpace
{
    // Forward declarations
    class Scene;
    class Entity;

    class Game
    {
    public:
		Game(std::string const& windowTitle, unsigned int screenWidth, unsigned int screenHeight, WindowStyle style = WindowStyle::DEFAULT);
        Game(std::string const& windowTitle, WindowStyle style = WindowStyle::DEFAULT);
        ~Game();

        void start();
        void setCurrentScene(EScene scene);

        // Helper functions.
    private:
        void checkGlobalInput();

    private:
        sf::RenderWindow window; 		  // Window of the Game.
        std::map<EScene, Scene *> scenes; // All Scenes of the Game.
        Scene *currentScene; 			  // Scene that is currently active (is drawn and updated).
        float windowWidth;
        float windowHeight;

        InputManager *inputManager;
        InputContext inputContext;

		bool frozen; // If this is true, the Game stops in time. TODO: Better explanation.

        // Global Entities/Drawables
    private:
        FpsCounter fpsCounter;

        Button exitBtn;
        Button closeMenuBtn;
        Button debugSceneBtn;
        Button sceneOneBtn;
        Button cronoTriggerSceneBtn;
        Button collisionSceneBtn;
        VBox btnBox;
        ButtonMenu buttonMenu;
        TranslateAnimation menuTa;

        std::vector<Entity *> globalEntities; 		    // Entities that get updated independent of any specific Scene.
        std::vector<sf::Drawable *> globalDrawables;
    };
}

#endif