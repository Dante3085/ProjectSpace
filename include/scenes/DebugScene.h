
#ifndef DEBUG_SCENE_H
#define DEBUG_SCENE_H

#include <SFML/Window/Window.hpp>

#include "input/InputManager.h"
#include "Scene.h"
#include "animation/AnimatedSprite.h"
#include "animation/Animation.h"
#include "animation/TranslateAnimation.h"

namespace ProjectSpace
{
	class DebugScene : public Scene
	{
	public:
		DebugScene(sf::RenderWindow& window);

		void update(sf::Time time) override;

	private:
		Animation animMagicSpell;
		Animation animMagic8;
		Animation animBlueFire;
		Animation animCasting;
		Animation animMagicHit;
		Animation animFlameLash;
		Animation animFireSpin;
		Animation animProtectionCircle;
		Animation animBrightFire;
		Animation animWeaponHit;
		Animation animFire;
		Animation animNebula;
		Animation animVortex;
		Animation animPhantom;
		Animation animLoading;
		Animation animSunburn;
		Animation animFelSpell;
		Animation animMidknight;
		Animation animFreezing;
		Animation animMagicBubble;

		AnimatedSprite magicSpell;
		AnimatedSprite magic8;
		AnimatedSprite blueFire;
		AnimatedSprite casting;
		AnimatedSprite magicHit;
		AnimatedSprite flameLash;
		AnimatedSprite fireSpin;
		AnimatedSprite protectionCircle;
		AnimatedSprite brightFire;
		AnimatedSprite weaponHit;
		AnimatedSprite fire;
		AnimatedSprite nebula;
		AnimatedSprite vortex;
		AnimatedSprite phantom;
		AnimatedSprite loading;
		AnimatedSprite sunburn;
		AnimatedSprite felSpell;
		AnimatedSprite midknight;
		AnimatedSprite freezing;
		AnimatedSprite magicBubble;

		TranslateAnimation ta;
		TranslateAnimation ta2;
		TranslateAnimation ta3;
	};
}

#endif