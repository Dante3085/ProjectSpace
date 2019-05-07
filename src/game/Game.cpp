
#include "Game.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../menu/ButtonMenu.h"
#include "../animation/TranslateAnimation.h"
#include "../menu/VBox.h"
#include "../menu/HBox.h"
#include "../game/InputHandler.h"
#include "../game/FpsCounter.h"
#include "../menu/TextBox.h"
#include "../animation/FadeAnimation.h"
#include "../menu/Button.h"
#include "../menu/ButtonMenu.h"
#include "InputHandler.h"
#include "Scene.h"
#include "Factory.h" 

namespace ProjectSpace
{
	Game::Game(std::string windowTitle, WindowStyle style)
	: window{sf::VideoMode{sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height}, windowTitle, style},
	currentScene{nullptr}, windowWidth{(float)sf::VideoMode::getDesktopMode().width}, windowHeight{(float)sf::VideoMode::getDesktopMode().height}
	{
		window.setFramerateLimit(61);

		init();
	}

	Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string windowTitle, WindowStyle style) 
	: window{sf::VideoMode{screenWidth, screenHeight}, windowTitle, style}, currentScene{nullptr}
	{
		// Makes sure that not more than 60 Frames per Second are calculated. Save Ressources.
		window.setFramerateLimit(61);

		init();
	}

	Game::~Game()
	{
		for (auto const& p : scenes)
		{
			delete p.second;
		}

		for (Entity* e : globalEntities)
		{
			delete e;
		}
	}
	
	void Game::start()
	{
		sf::Clock clock{};

		// This is main Game-Loop
		while (window.isOpen())
		{
			// At the start of each iteration "clock.restart()" will return the time that the last iteration took.
			// This is so that all objects of the current iteration know how much time has passed since the last frame.
			sf::Time time = clock.restart();
			float frameTime = time.asSeconds();
			
			// std::cout << "frameTime: " << frameTime << ", fps: " << 1.0f / frameTime << std::endl;

			// This is the Event-Loop (Hier muessen wir nochmal gucken, was wir damit anstellen koennen. Ist wohl ziemlich wichtig in SFML.)
			sf::Event event;
			while (window.pollEvent(event))
			{
				// For example by pressing the Close-Button on a Window, a Closed Event is created.
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			// Update all Entities...
			currentScene->update(time);
			for (Entity* e : globalEntities)
			{
				e->update(time);
			}

			// Draw all Drawables...
			window.clear();

			window.draw(*currentScene);
			for (sf::Drawable* d : globalDrawables)
			{
				window.draw(*d);
			}

			window.display();
		}
	}

	void Game::setCurrentScene(EScene scene)
	{
		if (scenes.count(scene) == 0)
		{
			std::cout << "@Game::setCurrentScene(): Given scene is not known to Game." << std::endl;
			return;
		}

		currentScene = scenes[scene];
	}

	void Game::init()
	{
		// Creating Levels
		scenes[EScene::DEBUG] = Factory::CREATE_DEBUG_SCENE(window);
		scenes[EScene::LEVEL_ONE] = Factory::CREATE_DEBUG_SCENE_2(window);
		scenes[EScene::TILEMAP] = Factory::CREATE_TILEMAP_SCENE(window);
		currentScene = scenes[EScene::DEBUG];

		// Fps Counter of the Game.
		FpsCounter* fpsCounter = new FpsCounter{"rsrc/fonts/arial.ttf"};

		// InputHandler for input Actions that are always available in the game independent of any specific Scene.
		InputHandler* globalInputHandler = new InputHandler{};

		// These 4 instances make up a global ButtonMenu (independent of any specific Scene).
		VBox* btnBox = new VBox{};
		TranslateAnimation* menuForward;
		TranslateAnimation* menuBackward;
		ButtonMenu* buttonMenu;

		// Creating Menu
		Button* btn = new Button{[this]()
		{
			window.close();
		}, window, "EXIT"};

		Button* btn2 = new Button{ window, "Close Menu" };

		Button* btn3 = new Button{[this]()
		{
			setCurrentScene(EScene::DEBUG);
		}, window, "Debug Level"};

		Button* btn4 = new Button{[this]()
		{
			setCurrentScene(EScene::LEVEL_ONE);
		}, window, "Level 1"};

		Button* btn5 = new Button{ [this]()
		{
			setCurrentScene(EScene::TILEMAP);
		}, window, "Tilemap Level" };

		btnBox->addMenuElements({btn, btn2, btn3, btn4, btn5});
		btnBox->setPosition(-10, 50);
		btnBox->setSpacing(5);

		buttonMenu = new ButtonMenu{{btn, btn2, btn3, btn4, btn5}, globalInputHandler};

		menuForward = new TranslateAnimation{btnBox, sf::Vector2f{-250, 50}, sf::Vector2f{-10, 50}, 0.5f};
		menuBackward = new TranslateAnimation{btnBox, sf::Vector2f{-10, 50}, sf::Vector2f{-250, 50}, 0.5f};

		btn2->setOnPressed([this, menuBackward]()
		{
			menuBackward->start();
		});

		// Setting up input handler
		globalInputHandler->storeKeyState(sf::Keyboard::F1, false);
		globalInputHandler->add([this, menuBackward, menuForward, globalInputHandler, fpsCounter]()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				menuBackward->stop();
				menuForward->start();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				menuForward->stop();
				menuBackward->start();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !globalInputHandler->wasKeyPressed(sf::Keyboard::F1))
			{
				if (fpsCounter->isHidden())
				{
					fpsCounter->setHide(false);
				}
				else
				{
					fpsCounter->setHide(true);
				}
			}

			globalInputHandler->storeKeyState(sf::Keyboard::F1, sf::Keyboard::isKeyPressed(sf::Keyboard::F1));
		});

		globalEntities = {fpsCounter, globalInputHandler, btnBox, menuForward, menuBackward, buttonMenu};
		globalDrawables = {fpsCounter, btnBox};
	}
}