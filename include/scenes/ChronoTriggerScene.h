
#ifndef CHRONO_TRIGGER_SCENE_H
#define CHRONO_TRIGGER_SCENE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "tilemap/Tilemap.h"
#include "animation/Animation.h"
#include "animation/AnimatedSprite.h"
#include "animation/FadeAnimation.h"
#include "animation/TranslateAnimation.h"
#include "Scene.h"
#include "Camera.h"
#include "gui/TextBox.h"
#include "gui/CombatOrder.h"
#include "gui/List.h"
#include "rpg/Character.h"
#include "audio/AudioFader.h"

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

		Camera camera;
		TextBox textBox;

		Character char1;
		Character char2;
		Character char3;
		Character char4;
		Character char5;
		CombatOrder combatOrder;

		sf::Music marvinTrack;
		AudioFader audioFader;

		List list;
		TranslateAnimation translateAnimation;
		FadeAnimation fadeAnimation;
		List list2;
		List list3;

		sf::SoundBuffer soundBuffer;
		sf::Sound sound;
	};
}

#endif