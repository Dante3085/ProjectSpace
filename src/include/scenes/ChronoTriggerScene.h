
#ifndef CHRONO_TRIGGER_SCENE_H
#define CHRONO_TRIGGER_SCENE_H

#include "tilemap/Tilemap.h"
#include "animation/Animation.h"
#include "animation/AnimatedSprite.h"
#include "animation/FadeAnimation.h"
#include "animation/TranslateAnimation.h"
#include "Scene.h"
#include "Camera.h"
#include "gui/TextBox.h"
#include "gui/BattleOrder.h"
#include "rpg/Character.h"

namespace ProjectSpace
{
	class ChronoTriggerScene : public Scene
	{
	public:
		ChronoTriggerScene(sf::RenderWindow& window);

		void update(sf::Time time) override;

	private:
		Tilemap tilemap;

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
		TextBox textBox;

		Character char1;
		Character char2;
		Character char3;
		BattleOrder battleOrder;
	};
}

#endif