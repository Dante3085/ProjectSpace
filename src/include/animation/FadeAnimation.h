
#ifndef FADE_ANIMATION_H
#define FADE_ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>

#include "scenes/Entity.h"
#include "animation/Easing.h"
#include "animation/Fadeable.h"

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