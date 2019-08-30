
#include "Game.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Mouse.hpp>

#include "ButtonMenu.h"
#include "TranslateAnimation.h"
#include "VBox.h"
#include "HBox.h"
#include "InputHandler.h"
#include "FpsCounter.h"
#include "TextBox.h"
#include "FadeAnimation.h"
#include "Button.h"
#include "ButtonMenu.h"
#include "InputHandler.h"
#include "Scene.h"
#include "Factory.h" 
#include "Util.h"
#include "Log.h"
#include "DebugScene.h"
#include "ChronoTriggerScene.h"

namespace ProjectSpace
{
	Game::Game(std::string windowTitle, WindowStyle style)
	: window{sf::VideoMode{sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height}, windowTitle, style},
	currentScene{nullptr}, windowWidth{(float)sf::VideoMode::getDesktopMode().width}, 
		windowHeight{(float)sf::VideoMode::getDesktopMode().height}
	{
		init();
	}

	Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string windowTitle, WindowStyle style) 
	: window{sf::VideoMode{screenWidth, screenHeight}, windowTitle, style}, currentScene{nullptr}
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

		// This is main Game-Loop
		std::string strFrameTime{""};
		int counter = 0;
		while (window.isOpen())
		{
			// At the start of each iteration "clock.restart()" will return the time that the last iteration took.
			// This is so that all objects of the current iteration know how much time has passed since the last frame.
			sf::Time time = clock.restart();
			float frameTime = time.asSeconds();
			
			/*strFrameTime.append("frameTime: ");
			strFrameTime.append(std::to_string(frameTime));
			strFrameTime.append(" ");
			strFrameTime.append("fps: ");
			strFrameTime.append(std::to_string(1.0f / frameTime));
			strFrameTime.append("\n");

			if (counter == 10)
			{
				std::cout << strFrameTime;
				strFrameTime.clear();
				counter = 0;
			}*/

			// std::cout << sf::Mouse::getPosition() << "\n";

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

			++counter;
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
		scenes[EScene::DEBUG] = new DebugScene{window};
		scenes[EScene::CHRONO_TRIGGER] = new ChronoTriggerScene{ window };
		scenes[EScene::LEVEL_ONE] = Factory::create_empty_scene(window);
		scenes[EScene::COLLISION_SCENE] = Factory::create_collision_scene(window);
		currentScene = scenes[EScene::CHRONO_TRIGGER];

		// Fps Counter of the Game.
		FpsCounter* fpsCounter = new FpsCounter{"rsrc/fonts/arial.ttf"};

		// InputHandler for input Actions that are always available in the game independent of any specific Scene.
		InputHandler* globalInputHandler = new InputHandler{};

		// These 4 instances make up a global ButtonMenu (independent of any specific Scene).
		VBox* btnBox = new VBox{};
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
		}, window, "Debug Scene"};

		Button* btn4 = new Button{[this]()
		{
			setCurrentScene(EScene::LEVEL_ONE);
		}, window, "Scene 1"};

		Button* btn5 = new Button{ [this]()
		{
			setCurrentScene(EScene::CHRONO_TRIGGER);
		}, window, "ChronoTrigger Scene" };

		Button* btn6 = new Button{ [this]()
		{
			setCurrentScene(EScene::COLLISION_SCENE);
		}, window, "Collision Scene" };

		Button* b0 = new Button{ [this]() {}, window, "b0" };
		Button* b1 = new Button{ [this]() {}, window, "b1" };
		Button* b2 = new Button{ [this]() {}, window, "b2" };
		Button* b3 = new Button{ [this]() {}, window, "b3" };
		VBox* vbox = new VBox{ {b2, b3}, sf::Vector2f{0, 0}, 5 };
		HBox* hbox = new HBox{ {b0, b1, vbox}, sf::Vector2f{0, 0}, 5 };

		btnBox->addMenuElements({btn, btn2, btn3, btn4, btn5, btn6, hbox});
		btnBox->setPosition(-10, 50);
		btnBox->setSpacing(5);

		buttonMenu = new ButtonMenu{{btn, btn2, btn3, btn4, btn5, btn6}, 
			globalInputHandler};

		float btnBoxWidth = btnBox->getWidth();
		TranslateAnimation* menuTa;
		menuTa = new TranslateAnimation{ *btnBox, sf::Vector2f{-250-btnBoxWidth, 50}, sf::Vector2f{-5, 50}, 300 };

		btn2->setOnPressed([btnBoxWidth, menuTa]()
		{
				menuTa->setFrom(menuTa->getTranslatable().getPosition());
				menuTa->setTo(sf::Vector2f{ -250 - btnBoxWidth, 50 });
				menuTa->setEasingFunction(Easing::quad_easeIn);
				menuTa->start();
		});

		// Setting up input handler
		using key = sf::Keyboard;
		globalInputHandler->storeKeyState(key::F1, false);
		globalInputHandler->storeKeyState(key::Tab, false);
		globalInputHandler->storeKeyState(key::E, false);
		globalInputHandler->storeKeyState(key::R, false);
		globalInputHandler->add([this, menuTa, btnBoxWidth, globalInputHandler, fpsCounter]()
		{
			if (key::isKeyPressed(key::Escape))
			{
				window.close();
			}

			if (!globalInputHandler->wasKeyPressed(key::E) && key::isKeyPressed(key::E))
			{
				menuTa->setFrom(menuTa->getTranslatable().getPosition());
				menuTa->setTo(sf::Vector2f{ -5, 50 });
				menuTa->setEasingFunction(Easing::sine_easeInOut);
				menuTa->start();
			}

			if (!globalInputHandler->wasKeyPressed(key::R) && key::isKeyPressed(key::R))
			{
				menuTa->setFrom(menuTa->getTranslatable().getPosition());
				menuTa->setTo(sf::Vector2f{ -250 - btnBoxWidth, 50 });
				menuTa->setEasingFunction(Easing::sine_easeInOut);
				menuTa->start();
			}

			if (key::isKeyPressed(key::F1) && !globalInputHandler->wasKeyPressed(key::F1))
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
			globalInputHandler->storeKeyState(key::F1, key::isKeyPressed(key::Tab));
			globalInputHandler->storeKeyState(key::E, key::isKeyPressed(key::E));
			globalInputHandler->storeKeyState(key::R, key::isKeyPressed(key::R));
		});

		globalEntities = {fpsCounter, globalInputHandler, btnBox, menuTa, buttonMenu};
		globalDrawables = {fpsCounter, btnBox};
	}
}