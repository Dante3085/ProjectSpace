
#ifndef CHRONO_TRIGGER_SCENE_H
#define CHRONO_TRIGGER_SCENE_H

#include "tilemap/Tilemap.h"
#include "animation/Animation.h"
#include "animation/AnimatedSprite.h"
#include "animation/FadeAnimation.h"
#include "animation/TranslateAnimation.h"
#include "Scene.h"
#include "Camera.h"

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
			crono{ sf::Vector2f{200, 200} }, cronoSpeed{8},
			wWasDown{false}, aWasDown{false}, sWasDown{false}, dWasDown{false}, spaceWasDown{false},
			rWasDown{false}, fadeAnimation{crono, 255, 0, 1000},
			translateAnimation{crono, sf::Vector2f{500, 500}, sf::Vector2f{1000, 500}, 2000},
			camera{crono, window, sf::Vector2f{200, 200}}
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

			Scene::addEntities({&crono, &fadeAnimation, &translateAnimation, &camera});
			Scene::addDrawables({&tilemap, &crono});
		}

		void update(sf::Time time) override
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
				translateAnimation.start();
			}

			if (!rWasDown && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				fadeAnimation.reset();
			}

			wWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			aWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			sWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			dWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			spaceWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			rWasDown = sf::Keyboard::isKeyPressed(sf::Keyboard::R);

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

		int cronoSpeed;

		bool wWasDown;
		bool aWasDown;
		bool sWasDown;
		bool dWasDown;
		bool spaceWasDown;
		bool rWasDown;

		FadeAnimation fadeAnimation;
		TranslateAnimation translateAnimation;
		Camera camera;
	};
}

#endif