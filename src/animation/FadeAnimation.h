
#ifndef FADE_ANIMATION
#define FADE_ANIMATION

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "../game/Entity.h"

namespace ProjectSpace
{
	/**
	 * @brief      For Fading Sprites in and out. (Bin mir nicht sicher, ob Fading so implementiert werden sollte. Koennen wir nochmal komplett neu machen.)
	 */
	class FadeAnimation : public Entity
	{
	public:
		FadeAnimation(sf::Sprite* sprite, float duration);
		
		void update(sf::Time time) override;
		void start();
		void refresh();

	private:
		sf::Sprite* sprite;
		sf::Color color;
		float amount;
		float delay;
		float elapsedSeconds;
		bool doUpdate;
	};
}

#endif