
#include "Game.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Mouse.hpp>

#include "gui/ButtonMenu.h"
#include "gui/VBox.h"
#include "gui/HBox.h"
#include "gui/FpsCounter.h"
#include "gui/TextBox.h"
#include "gui/Button.h"
#include "gui/ButtonMenu.h"
#include "animation/TranslateAnimation.h"
#include "animation/FadeAnimation.h"
#include "input/InputHandler.h"
#include "scenes/Scene.h"
#include "scenes/DebugScene.h"
#include "scenes/ChronoTriggerScene.h"
#include "utility/Util.h"
#include "utility/Log.h"

namespace ProjectSpace
{
	Game::Game(std::string const& windowTitle, WindowStyle style)
		: window{ sf::VideoMode{sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height}, windowTitle, style },
		currentScene{ nullptr }, windowWidth{ (float)sf::VideoMode::getDesktopMode().width },
		windowHeight{ (float)sf::VideoMode::getDesktopMode().height },
		inputManager{&InputManager::getInstance()}
	{
		init();
	}

	Game::Game(std::string const& windowTitle, unsigned int screenWidth, unsigned int screenHeight, WindowStyle style)
		: window{ sf::VideoMode{screenWidth, screenHeight}, windowTitle, style }, currentScene{ nullptr }
	{
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

		// Was mache ich jetzt, wenn Drawables die keine Entities sind existieren ?
	}

	void Game::start()
	{
		sf::Clock clock{};

		while (window.isOpen())
		{
			inputManager->updateCurrentKeys();
			inputManager->updateInputContexts();

			// At the start of each iteration "clock.restart()" will return the time that the last iteration took.
			// This is so that all objects of the current iteration know how much time has passed since the last frame.
			sf::Time time = clock.restart();

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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				window.close();
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

			inputManager->updatePreviousKeys();
		}
	}

	void Game::setCurrentScene(EScene scene)
	{
		if (scenes.count(scene) == 0)
		{
			Log::getInstance() << lo::PTC << ll::ERR << lo::TIMESTAMP << "Given scene is not known to Game."
				<< lo::STACKTRACE << lo::END;
			return;
		}

		currentScene = scenes[scene];
	}

	void Game::init()
	{
		window.setFramerateLimit(60);

		// Creating Scenes
		scenes[EScene::DEBUG] = new DebugScene{ window };
		scenes[EScene::CHRONO_TRIGGER] = new ChronoTriggerScene{ window };
		currentScene = scenes[EScene::CHRONO_TRIGGER];

		// Fps Counter of the Game.
		FpsCounter* fpsCounter = new FpsCounter{ "rsrc/fonts/arial.ttf" };

		// InputHandler for input Actions that are always available in the game independent of any specific Scene.
		InputHandler* globalInputHandler = new InputHandler{};

		// These 4 instances make up a global ButtonMenu (independent of any specific Scene).
		VBox* btnBox = new VBox{};
		ButtonMenu* buttonMenu;

		// Creating Menu
		Button* btn = new Button{ [this]()
		{
			window.close();
		}, window, "EXIT" };

		Button* btn2 = new Button{ window, "Close Menu" };

		Button* btn3 = new Button{ [this]()
		{
			setCurrentScene(EScene::DEBUG);
		}, window, "Debug Scene" };

		Button* btn4 = new Button{ [this]()
		{
			setCurrentScene(EScene::LEVEL_ONE);
		}, window, "Scene 1" };

		Button* btn5 = new Button{ [this]()
		{
			setCurrentScene(EScene::CHRONO_TRIGGER);
		}, window, "ChronoTrigger Scene" };

		Button* btn6 = new Button{ [this]()
		{
			setCurrentScene(EScene::COLLISION_SCENE);
		}, window, "Collision Scene" };

		btnBox->addMenuElements({ btn, btn2, btn3, btn4, btn5, btn6 });
		btnBox->setPosition(-10, 50);
		btnBox->setSpacing(5);

		buttonMenu = new ButtonMenu{ {btn, btn2, btn3, btn4, btn5, btn6},
			globalInputHandler };

		float btnBoxWidth = btnBox->getWidth();
		TranslateAnimation* menuTa;
		menuTa = new TranslateAnimation{ *btnBox, sf::Vector2f{-250 - btnBoxWidth, 50}, sf::Vector2f{-5, 50}, 500 };
		menuTa->start();

		btn2->setOnPressed([btnBoxWidth, menuTa]()
			{
				menuTa->setFrom(menuTa->getTranslatable().getPosition());
				menuTa->setTo(sf::Vector2f{ -250 - btnBoxWidth, 50 });
				menuTa->setEasingFunction(Easing::back_easeInOut);
				menuTa->start();
			});

		// Setting up input handler
		using key = sf::Keyboard;
		globalInputHandler->storeKeyState(key::F1, false);
		globalInputHandler->storeKeyState(key::Tab, false);
		globalInputHandler->storeKeyState(key::E, false);
		globalInputHandler->storeKeyState(key::R, false);
		globalInputHandler->storeKeyState(key::Tab, false);
		globalInputHandler->add([this, menuTa, btnBoxWidth, globalInputHandler, fpsCounter, btnBox]()
			{
				if (!globalInputHandler->wasKeyPressed(key::Tab) && key::isKeyPressed(key::Tab))
				{
					if (menuTa->getTo() == sf::Vector2f{ -250 - btnBoxWidth, 50 })
					{
						menuTa->setFrom(menuTa->getTranslatable().getPosition());
						menuTa->setTo(sf::Vector2f{ -5, 50 });
						menuTa->setEasingFunction(Easing::back_easeInOut);
						menuTa->start();
					}
					else
					{
						menuTa->setFrom(menuTa->getTranslatable().getPosition());
						menuTa->setTo(sf::Vector2f{ -250 - btnBoxWidth, 50 });
						menuTa->setEasingFunction(Easing::back_easeInOut);
						menuTa->start();
					}
				}

				if (!globalInputHandler->wasKeyPressed(key::F1) && key::isKeyPressed(key::F1))
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

				globalInputHandler->storeKeyState(key::F1, key::isKeyPressed(key::F1));
				globalInputHandler->storeKeyState(key::E, key::isKeyPressed(key::E));
				globalInputHandler->storeKeyState(key::R, key::isKeyPressed(key::R));
				globalInputHandler->storeKeyState(key::Tab, key::isKeyPressed(key::Tab));
			});

		globalEntities = { fpsCounter, globalInputHandler, btnBox, menuTa/*, buttonMenu*/ };
		globalDrawables = { fpsCounter, btnBox };
	}
}