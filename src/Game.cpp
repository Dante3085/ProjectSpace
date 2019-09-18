
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
	Game::Game(std::string const& windowTitle, unsigned int screenWidth, unsigned int screenHeight, WindowStyle style)
		: window{ sf::VideoMode{screenWidth, screenHeight}, windowTitle, style },
		scenes{},
		currentScene{ nullptr },
		windowWidth{ (float)sf::VideoMode::getDesktopMode().width },
		windowHeight{ (float)sf::VideoMode::getDesktopMode().height },
		inputManager{ &InputManager::getInstance() },
		inputContext{ "include/input/contexts/GlobalContext.txt" },
		frozen{ false },
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

		exitBtn.setOnPressed([this]()
			{
				inputContext.fireAction(Action::EXIT_GAME);
			});

		closeMenuBtn.setOnPressed([this]()
			{
				inputContext.fireAction(Action::GLOBAL_MENU_TOGGLE);
			});

		debugSceneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::DEBUG);
			});

		sceneOneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::LEVEL_ONE);
			});

		cronoTriggerSceneBtn.setOnPressed([this]()
			{
				setCurrentScene(EScene::CHRONO_TRIGGER);
			});

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
    }

    void Game::start()
    {
        sf::Clock clock{};

        while (window.isOpen())
        {
			sf::Time time = clock.restart();

            inputManager->updateCurrentKeys();
            inputManager->updateInputContexts();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

			if (inputContext.hasActionFired(Action::FREEZE_GAME_TOGGLE))
			{
				frozen = frozen ? false : true;
			}

			if (!frozen)
			{
				checkGlobalInput();

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