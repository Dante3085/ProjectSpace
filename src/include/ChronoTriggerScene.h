#pragma once

#include "Scene.h"
#include "Tilemap.h"
#include "Animation.h"
#include "AnimatedSprite.h"

namespace ProjectSpace
{
	class ChronoTriggerScene : public Scene
	{
	public:
		ChronoTriggerScene(sf::RenderWindow& window)
			: Scene{window}, tilemap{"rsrc/SNES - Chrono Trigger - Court Room.gif"},
			cronoIdle{"rsrc/CronoTransparentBackground.png"},
			cronoWalkLeft{ "rsrc/CronoTransparentBackground.png" },
			cronoWalkUp{ "rsrc/CronoTransparentBackground.png" },
			cronoWalkRight{ "rsrc/CronoTransparentBackground.png" },
			cronoWalkDown{"rsrc/CronoTransparentBackground.png"},
			wWasDown{false}, aWasDown{false}, sWasDown{false}, dWasDown{false},
			crono{sf::Vector2f{200, 200}}
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

			Scene::addEntities({&crono});
			Scene::addDrawables({&tilemap, &crono});
		}

		void update(sf::Time time) override
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				crono.setAnimation(EAnimation::UP);
				crono.move(0, -5);
			}
			else if (wWasDown)
			{
				crono.setAnimation(EAnimation::IDLE);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				crono.setAnimation(EAnimation::LEFT);
				crono.move(-5, 0);
			}
			else if (aWasDown)
			{
				crono.setAnimation(EAnimation::IDLE);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				crono.setAnimation(EAnimation::DOWN);
				crono.move(0, 5);
			}
			else if (sWasDown)
			{
				crono.setAnimation(EAnimation::IDLE);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				crono.setAnimation(EAnimation::RIGHT);
				crono.move(5, 0);
			}
			else if (dWasDown)
			{
				crono.setAnimation(EAnimation::IDLE);
			}

			wWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			aWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			sWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			dWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

			Scene::update(time);
		}

	private:
		TileMap tilemap;

		Animation cronoIdle;
		Animation cronoWalkLeft;
		Animation cronoWalkUp;
		Animation cronoWalkRight;
		Animation cronoWalkDown;
		AnimatedSprite crono;

		bool wWasDown;
		bool aWasDown;
		bool sWasDown;
		bool dWasDown;
	};
}