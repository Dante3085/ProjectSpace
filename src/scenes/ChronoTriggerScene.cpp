
#include "scenes/ChronoTriggerScene.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "utility/Util.h"

namespace ProjectSpace
{
	ChronoTriggerScene::ChronoTriggerScene(sf::RenderWindow& window)
		: Scene{ window }, tilemap{ "rsrc/tilesets/SNES - Chrono Trigger - Court Room.gif" },
		cronoIdle{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkLeft{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkUp{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkRight{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkDown{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		crono{ sf::Vector2f{200, 200} }, cronoSpeed{ 8 },
		wWasDown{ false }, aWasDown{ false }, sWasDown{ false }, dWasDown{ false }, spaceWasDown{ false },
		rWasDown{ false }, fadeAnimation{ crono, 255, 0, 1000 },
		translateAnimation{ crono, sf::Vector2f{500, 500}, sf::Vector2f{1000, 500}, 2000 },
		camera{ crono, window, sf::Vector2f{200, 200} },
		textBox{"rsrc/backgrounds/blueTextbox.png", "Graphik, ist im weitesten Sinn der Sammelbegriff für alle künstlerischen oder technischen Zeichnungen sowie"
		"deren manuelle drucktechnische Vervielfältigung. In der engsten Begriffsverwendung bezieht sich Grafik allein auf die künstlerische Druckgrafik"
		", die zur bildenden Kunst gehört. Eine Originalgrafik entsteht eigenständig, unabhängig von Vorlagen und in der Absicht, die Techniken der Druckgrafik"
		"für den künstlerischen Ausdruck zu nutzen.",
				sf::Vector2f(1000,600), sf::Vector2f(200,200)},
		combatOrder{ {&char1, &char3}, {&char2, &char4}, {"rsrc/spritesheets/singleImages/hearts-1.png", 
		"rsrc/spritesheets/singleImages/knight iso char_slice down_2.png",
	    "rsrc/spritesheets/singleImages/hearts-1.png",
	    "rsrc/spritesheets/singleImages/sensei.png"}, sf::Vector2f{2000, 500} },
		audioFader{marvinTrack, 0, 100, 3000}
	{
		tilemap.loadFromFile("tilemaps/chronoTriggerScene.txt");

		cronoIdle.setAnimation({ {59, 14, 15, 34}, {79, 14, 15, 34}, {99, 14, 15, 34} }, 0.8f);
		cronoWalkLeft.setAnimation({ {34, 683, 14, 33}, {56, 684, 13, 32}, {75, 685, 21, 31}, {103, 683, 13, 33},
									 {125, 684, 14, 32}, {145, 685, 20, 32} }, 0.15f);
		cronoWalkUp.setAnimation({ {130, 59, 17, 32}, {152, 60, 17, 31}, {174, 57, 15, 34}, {193, 57, 15, 34},
								   {213, 60, 17, 31}, {235, 59, 17, 32} }, 0.15f);
		cronoWalkRight.setAnimation({ {126, 100, 19, 31}, {151, 99, 14, 32}, {174, 98, 13, 33}, {194, 100, 21, 31},
									  {221, 99, 13, 32}, {242, 98, 14, 33} }, 0.15f);
		cronoWalkDown.setAnimation({ sf::IntRect{130, 15, 15, 33}, {150, 17, 16, 31}, {171, 14, 17, 34},
								  {193, 15, 15, 33}, {213, 17, 16, 31} }, 0.15f);

		crono.addAnimation(EAnimation::IDLE, &cronoIdle);
		crono.addAnimation(EAnimation::LEFT, &cronoWalkLeft);
		crono.addAnimation(EAnimation::UP, &cronoWalkUp);
		crono.addAnimation(EAnimation::RIGHT, &cronoWalkRight);
		crono.addAnimation(EAnimation::DOWN, &cronoWalkDown);
		crono.setAnimation(EAnimation::IDLE);
		crono.setScale(6, 6);

		translateAnimation.setEasingFunction(Easing::linear_easeNone);
		
		textBox.setPadding(25);
		//// textBox.setPosition(1000, 1000);
		//textBox.setPosition(sf::Vector2f{ 1000, 1000 });
		//textBox.setSize(2000, 400);

		marvinTrack.openFromFile("rsrc/audio/music/Klassik Soundtrack 1.ogg");
		
		Scene::addEntities({ &crono, &fadeAnimation, &camera, &textBox, &combatOrder, &audioFader});
		Scene::addDrawables({ &tilemap, &crono, &textBox, &combatOrder });
	}

	void ChronoTriggerScene::update(sf::Time time)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			crono.setAnimation(EAnimation::UP);
			crono.move(0, -cronoSpeed);
		}
		else if (wWasDown)
		{
			crono.setAnimation(EAnimation::IDLE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			crono.setAnimation(EAnimation::LEFT);
			crono.move(-cronoSpeed, 0);
		}
		else if (aWasDown)
		{
			crono.setAnimation(EAnimation::IDLE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			crono.setAnimation(EAnimation::DOWN);
			crono.move(0, cronoSpeed);
		}
		else if (sWasDown)
		{
			crono.setAnimation(EAnimation::IDLE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			crono.setAnimation(EAnimation::RIGHT);
			crono.move(cronoSpeed, 0);
		}
		else if (dWasDown)
		{
			crono.setAnimation(EAnimation::IDLE);
		}

		if (!spaceWasDown && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			combatOrder.cycle();
		}

		if (!rWasDown && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (marvinTrack.getVolume() == 100)
			{
				audioFader.setStartVolume(100);
				audioFader.setEndVolume(0);
				audioFader.setEasingFunction(Easing::sine_easeOut);
			}
			else
			{
				audioFader.setStartVolume(0);
				audioFader.setEndVolume(100);
				audioFader.setEasingFunction(Easing::sine_easeIn);
			}
			audioFader.start();
		}

		wWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		aWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		sWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		dWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		spaceWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		rWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		
		Scene::update(time);
	}
}
