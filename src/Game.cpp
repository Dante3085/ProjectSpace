
#include "Game.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Mouse.hpp>

#include "scenes/Scene.h"
#include "scenes/Entity.h"
#include "scenes/DebugScene.h"
#include "scenes/ChronoTriggerScene.h"
#include "utility/Util.h"
#include "utility/Log.h"

namespace ProjectSpace
{
    Game::Game(std::string const &windowTitle, unsigned int screenWidth, unsigned int screenHeight, WindowStyle style)
        : window{ sf::VideoMode{screenWidth, screenHeight}, windowTitle, style },
		scenes{},
		currentScene{ nullptr },
		windowWidth{ (float)sf::VideoMode::getDesktopMode().width },
		windowHeight{ (float)sf::VideoMode::getDesktopMode().height },
		inputManager{ &InputManager::getInstance() },
		inputContext{ "include/input/contexts/GlobalContext.txt" },
		fpsCounter{ "rsrc/fonts/arial.ttf" },
		exitBtn{ window, "EXIT GAME" },
		closeMenuBtn{ window, "CLOSE MENU" },
		debugSceneBtn{ window, "DEBUG SCENE" },
		sceneOneBtn{ window, "SCENE ONE" },
		cronoTriggerSceneBtn{ window, "CHRONO TRIGGER SCENE" },
		collisionSceneBtn{ window, "COLLISION SCENE" },
		btnBox{},
		buttonMenu{ {&exitBtn, &closeMenuBtn, &debugSceneBtn, &sceneOneBtn, &cronoTriggerSceneBtn, &collisionSceneBtn} },
		menuTa{ btnBox, sf::Vector2f{-250 - btnBox.getWidth(), 50}, sf::Vector2f{-5, 50}, 500 },
		globalEntities{ &fpsCounter, &btnBox, &menuTa, &buttonMenu },
		globalDrawables{ &fpsCounter, &btnBox }
    {
		window.setFramerateLimit(60);

		// Creating Scenes
		scenes[EScene::DEBUG] = new DebugScene{ window };
		scenes[EScene::CHRONO_TRIGGER] = new ChronoTriggerScene{ window };
		currentScene = scenes[EScene::CHRONO_TRIGGER];

		// Fps Counter of the Game.
		// FpsCounter *fpsCounter = new FpsCounter{ "rsrc/fonts/arial.ttf" };

		// These 4 instances make up a global ButtonMenu (independent of any specific Scene).
		// VBox *btnBox = new VBox{};
		// ButtonMenu *buttonMenu;

		// Creating Menu
		/*Button *btn = new Button{ [this]()
		{
			window.close();
		}, window, "EXIT" };*/
		exitBtn.setOnPressed([this]()
			{
				inputContext.fireAction(Action::EXIT_GAME);
			});

		// Button *btn2 = new Button{ window, "Close Menu" };
		closeMenuBtn.setOnPressed([this]()
			{
				inputContext.fireAction(Action::GLOBAL_MENU_TOGGLE);
			});

		/*Button *btn3 = new Button{ [this]()
		{
			setCurrentScene(EScene::DEBUG);
		}, window, "Debug Scene" };*/
		debugSceneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::DEBUG);
			});

		/*Button *btn4 = new Button{ [this]()
		{
			setCurrentScene(EScene::LEVEL_ONE);
		}, window, "Scene 1" };*/
		sceneOneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::LEVEL_ONE);
			});

		/*Button *btn5 = new Button{ [this]()
		{
			setCurrentScene(EScene::CHRONO_TRIGGER);
		}, window, "ChronoTrigger Scene" };*/
		cronoTriggerSceneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::CHRONO_TRIGGER);
			});

		/*Button *btn6 = new Button{ [this]()
		{
			setCurrentScene(EScene::COLLISION_SCENE);
		}, window, "Collision Scene" };*/
		collisionSceneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::COLLISION_SCENE);
			});

		btnBox.addMenuElements({ &exitBtn, &closeMenuBtn, &debugSceneBtn, &sceneOneBtn, &cronoTriggerSceneBtn,
								 &collisionSceneBtn });
		btnBox.setPosition(-10, 50);
		btnBox.setSpacing(5);

		menuTa.start();

		inputContext.setPredicate([]()
			{
				return true;
			});
		inputManager->registerInputContext("Game", &inputContext);
    }

	Game::Game(std::string const& windowTitle, WindowStyle style)
		: Game{ windowTitle, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, style }
	{}

    Game::~Game()
    {
        for (auto const &p : scenes)
        {
            delete p.second;
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

            // TODO: This is the Event-Loop (Hier muessen wir nochmal gucken, was wir damit anstellen koennen.
            // Ist wohl ziemlich wichtig in SFML.
            sf::Event event;
            while (window.pollEvent(event))
            {
                // For example by pressing the Close-Button on a Window, a Closed Event is created.
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

			checkGlobalInput();

            // Update all Entities...
            currentScene->update(time);
            for (Entity *e : globalEntities)
            {
                e->update(time);
            }

            // Draw all Drawables...
            window.clear();

            window.draw(*currentScene);
            for (sf::Drawable *d : globalDrawables)
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

    void Game::checkGlobalInput()
    {
        // Global Input
        /*globalInputHandler->add([this, menuTa, btnBoxWidth, globalInputHandler, fpsCounter, btnBox]()
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
        	});*/

        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        	{
        		window.close();
        	}*/

        if (inputContext.hasActionFired(Action::EXIT_GAME))
        {
            window.close();
        }

        if (inputContext.hasActionFired(Action::GLOBAL_MENU_TOGGLE))
        {
            if (menuTa.getTo() == sf::Vector2f{ -250 - btnBox.getWidth(), 50 })
            {
                menuTa.setFrom(menuTa.getTranslatable().getPosition());
                menuTa.setTo(sf::Vector2f{ -5, 50 });
                menuTa.setEasingFunction(Easing::back_easeInOut);
                menuTa.start();
            }
            else
            {
                menuTa.setFrom(menuTa.getTranslatable().getPosition());
                menuTa.setTo(sf::Vector2f{ -250 - btnBox.getWidth(), 50 });
                menuTa.setEasingFunction(Easing::back_easeInOut);
                menuTa.start();
            }
        }

        if (inputContext.hasActionFired(Action::FPS_COUNTER_TOGGLE))
        {
			if (fpsCounter.isHidden())
			{
				fpsCounter.setHide(false);
			}
			else
			{
				fpsCounter.setHide(true);
			}
        }
    }
}