
#ifndef FADE_ANIMATION
#define FADE_ANIMATION

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "Entity.h"

namespace ProjectSpace
{
	/**
	 * @brief      For Fading Sprites in and out. (Bin mir nicht sicher, ob Fading so implementiert werden sollte. Koennen wir nochmal komplett neu machen.)
	 */
	class FadeAnimation : public Entity
	{
	public:

		/**
		 * @brief      Constructs a FadeAnimation with the given Sprite and duration.
		 *
		 * @param      sprite    The sprite
		 * @param[in]  duration  The duration
		 */
		FadeAnimation(sf::Sprite* sprite, float duration);
		

		/**
		 * @brief      Updates the FadeAnimation each frame.
		 *
		 * @param[in]  time  The time that has passed since last update call.
		 */
		void update(sf::Time time) override;

		/**
		 * @brief      Starts the FadeAnimation.
		 */
		void start();

		/**
		 * @brief      Puts the FadeAnimation in it's initial state.
		 */
		void refresh();

	private:
		sf::Sprite* sprite; // Sprite that the FadeAnimation will be used on.
		sf::Color color;	// For gradually updating the Sprite's Color.
		float amount;
		float delay;
		float elapsedSeconds;
		bool doUpdate;
	};
}

#endif