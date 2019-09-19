
#include "animation/FadeAnimation.h"

namespace ProjectSpace
{
	FadeAnimation::FadeAnimation(Fadeable& fadeable, int startAlpha, int endAlpha, int durationInMilliseconds)
		: fadeable{ fadeable }, 
		startAlpha{ startAlpha }, 
		endAlpha{ endAlpha }, 
		durationInMilliseconds{ durationInMilliseconds },
		elapsedMilliseconds{ 0 }, 
		doUpdate{ false }, 
		easingFunction{ Easing::sine_easeInOut }
	{
		fadeable.setColor(sf::Color( 255, 255, 255, startAlpha ));
	}

	void FadeAnimation::update(sf::Time time)
	{
		if (!doUpdate)
			return;

		sf::Color c( 255, 255, 255, -1 );
		c.a = easingFunction(elapsedMilliseconds, startAlpha, endAlpha - startAlpha, durationInMilliseconds);
		fadeable.setColor(c);

		elapsedMilliseconds += time.asMilliseconds();
		if (elapsedMilliseconds >= durationInMilliseconds)
		{
			c.a = endAlpha;
			fadeable.setColor(c);
			elapsedMilliseconds = 0;
			doUpdate = false;
			return;
		}
	}

	void FadeAnimation::start()
	{
		doUpdate = true;
	}

	void FadeAnimation::reset()
	{
		doUpdate = false;
		elapsedMilliseconds = 0;
		fadeable.setColor(sf::Color( 255, 255, 255, startAlpha ));
	}

	void FadeAnimation::setEasingFunction(Easing::EasingFunction easingFunction)
	{
		this->easingFunction = easingFunction;
	}

	void FadeAnimation::setStartAlpha(int startAlpha)
	{
		this->startAlpha = startAlpha;
	}

	void FadeAnimation::setEndAlpha(int endAlpha)
	{
		this->endAlpha = endAlpha;
	}

	int FadeAnimation::getStartAlpha()
	{
		return startAlpha;
	}

	int FadeAnimation::getEndAlpha()
	{
		return endAlpha;
	}
}