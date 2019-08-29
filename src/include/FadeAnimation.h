
#ifndef FADE_ANIMATION
#define FADE_ANIMATION

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>

#include "Entity.h"
#include "Easing.h"
#include "Fadeable.h"

namespace ProjectSpace
{
	class FadeAnimation : public Entity
	{
	public:
		FadeAnimation(Fadeable& fadeable, int startAlpha, int endAlpha, int durationInMilliseconds);

		void update(sf::Time time) override;
		void start();
		void reset();
		void setEasingFunction(Easing::EasingFunction easingFunction);

	private:
		Fadeable& fadeable;
		int startAlpha;
		int endAlpha;
		int durationInMilliseconds;
		int elapsedMilliseconds;
		bool doUpdate;

		Easing::EasingFunction easingFunction;
	};
}

#endif