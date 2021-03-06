
#include "scenes/ChronoTriggerScene.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "utility/Util.h"

namespace ProjectSpace
{
	// TODO: Crono Framerate independant speed(constant speed through different framerates).

	ChronoTriggerScene::ChronoTriggerScene(sf::RenderWindow& window)
		: Scene{ window }, 
		tilemap{ "rsrc/tilesets/SNES - Chrono Trigger - Court Room.gif" },
		cronoIdle{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkLeft{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkUp{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkRight{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		cronoWalkDown{ "rsrc/spritesheets/CronoTransparentBackground.png" },
		crono{ sf::Vector2f{200, 200} }, 
		cronoSpeed{ 12 },
		camera{ crono, window, sf::Vector2f{200, 200} },
		textBox{"rsrc/backgrounds/blueTextbox.png", "Graphik, ist im weitesten Sinn der Sammelbegriff für alle künstlerischen oder technischen Zeichnungen sowie"
		"deren manuelle drucktechnische Vervielfältigung. In der engsten Begriffsverwendung bezieht sich Grafik allein auf die künstlerische Druckgrafik"
		", die zur bildenden Kunst gehört. Eine Originalgrafik entsteht eigenständig, unabhängig von Vorlagen und in der Absicht, die Techniken der Druckgrafik"
		"für den künstlerischen Ausdruck zu nutzen.",
				sf::Vector2f(1000,300), sf::Vector2f(200,200)},
		combatOrder{ {&char1, &char3}, {&char2, &char4}, {"rsrc/spritesheets/singleImages/hearts-1.png", 
		"rsrc/spritesheets/singleImages/knight iso char_slice down_2.png",
	    "rsrc/spritesheets/singleImages/hearts-1.png",
	    "rsrc/spritesheets/singleImages/sensei.png"}, sf::Vector2f{2000, 500} },
		audioFader{marvinTrack, 0, 100, 3000},
		list{sf::Vector2f{100, 800},
	{
		{"Hi-Potion x 4", []() { std::cout << "ListItem0 gedrueckt!" << std::endl; }},
		{"Potion x 20", [this]() { sound.play(); }},
		{"Black-Spheroid x 20", []() {}},
		{"Hi-Ether x 20", []() {}},
		{"Antdoit x 20", []() {}},
		{"Elixir x 20", []() {}},
		{"Ether x 50", []() {}},
		{"Potion x 20", []() {}},
		{"Grenade x 6", []() {}},
		{"Potion x 20", []() {}},
		{"PhoenixDown x 2", []() {}},
		{"Potion x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Hi-Potion x 4", []() { std::cout << "ListItem0 gedrueckt!" << std::endl; }},
		{"Potion x 20", [this]() { sound.play(); }},
		{"Black-Spheroid x 20", []() {}},
		{"Hi-Ether x 20", []() {}},
		{"Antdoit x 20", []() {}},
		{"Elixir x 20", []() {}},
		{"Ether x 50", []() {}},
		{"Potion x 20", []() {}},
		{"Grenade x 6", []() {}},
		{"Potion x 20", []() {}},
		{"PhoenixDown x 2", []() {}},
		{"Potion x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},{"Hi-Potion x 4", []() { std::cout << "ListItem0 gedrueckt!" << std::endl; }},
		{"Potion x 20", [this]() { sound.play(); }},
		{"Black-Spheroid x 20", []() {}},
		{"Hi-Ether x 20", []() {}},
		{"Antdoit x 20", []() {}},
		{"Elixir x 20", []() {}},
		{"Ether x 50", []() {}},
		{"Potion x 20", []() {}},
		{"Grenade x 6", []() {}},
		{"Potion x 20", []() {}},
		{"PhoenixDown x 2", []() {}},
		{"Potion x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},{"Hi-Potion x 4", []() { std::cout << "ListItem0 gedrueckt!" << std::endl; }},
		{"Potion x 20", [this]() { sound.play(); }},
		{"Black-Spheroid x 20", []() {}},
		{"Hi-Ether x 20", []() {}},
		{"Antdoit x 20", []() {}},
		{"Elixir x 20", []() {}},
		{"Ether x 50", []() {}},
		{"Potion x 20", []() {}},
		{"Grenade x 6", []() {}},
		{"Potion x 20", []() {}},
		{"PhoenixDown x 2", []() {}},
		{"Potion x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
		{"Final-Elixir x 20", []() {}},
	}},
	inputContext{"include/input/contexts/ChronoTriggerSceneContext.txt"},
	collisionBox{ sf::Vector2f{400, 500}, sf::Vector2f{100, 100} },
	collisionManager{{&collisionBox, &crono}}
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

		// translateAnimation.setEasingFunction(Easing::linear_easeNone);
		
		//textBox.setPadding(50);
		//// textBox.setPosition(1000, 1000);
		//textBox.setPosition(sf::Vector2f{ 1000, 1000 });
		//textBox.setSize(2000, 400);

		marvinTrack.openFromFile("rsrc/audio/music/Klassik Soundtrack 1.ogg");
		
		soundBuffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg");
		sound.setBuffer(soundBuffer);

		Scene::addEntities({ &crono, /*&camera,*/ &textBox, 
			                 &combatOrder, &audioFader, &list});
		Scene::addDrawables({ &tilemap, &crono, &textBox, &combatOrder, &list, &collisionBox });

		inputContext.setPredicate([]()
			{
				return true;
			});
		InputManager::getInstance().registerInputContext("ChronoTriggerScene", &inputContext);
	}

	void ChronoTriggerScene::update(sf::Time time)
	{

		int anzahl[] = {0,0};
		sf::Vector2f currentPosition = crono.getPosition();
		if (inputContext.isStateOn(State::WALK_NORTH))
		{
			++anzahl[0];
			crono.setAnimation(EAnimation::UP);
			crono.move(0, -cronoSpeed);
		}
		if (inputContext.isStateOn(State::WALK_SOUTH))
		{
			++anzahl[0];
			crono.setAnimation(EAnimation::DOWN);
			crono.move(0, cronoSpeed);
		}
		if (inputContext.isStateOn(State::WALK_EAST))
		{
			++anzahl[1];
			crono.setAnimation(EAnimation::RIGHT);
			crono.move(cronoSpeed, 0);
		}
		if (inputContext.isStateOn(State::WALK_WEST))
		{
			++anzahl[1];
			crono.setAnimation(EAnimation::LEFT);
			crono.move(-cronoSpeed, 0);
		}
		if((anzahl[0] > 1)||(anzahl[1] > 1)||((anzahl[0] == 0) && (anzahl[1] == 0)))
		{
			crono.setPosition(currentPosition);
			crono.setAnimation(EAnimation::IDLE);
		}
		
		Scene::update(time);
	}
}
