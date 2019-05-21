
#include "FadeAnimation.h"

namespace ProjectSpace
{
	FadeAnimation::FadeAnimation(sf::Sprite* sprite, int startAlpha, int endAlpha, float alphaModifier) 
		: sprite{ sprite }, startAlpha{ startAlpha }, endAlpha{ endAlpha }, 
		 doUpdate{ false }, alphaVelocity((endAlpha - startAlpha) * alphaModifier) {}

	/*void FadeAnimation::update(sf::Time time)
	{
		if (doUpdate)
		{
			if (color.a > 0)
			{
				color.a -= amount;
				sprite->setColor(color);
			}
			elapsedSeconds += time.asSeconds();
		}
	}*/

	void FadeAnimation::update(sf::Time time)
	{
		if (doUpdate)
		{
			sf::Color fadeColor = sprite->getColor();
			fadeColor.a += alphaVelocity;
			sprite->setColor(fadeColor);
			alphaVelocity *= 0.8f;

			if (fadeColor.a == 0)
			{
				doUpdate = false;
			}
		}
	}

	void FadeAnimation::start()
	{
		doUpdate = true;
	}

	void FadeAnimation::refresh()
	{
		/*color.a = 255;
		sprite->setColor(color);
		elapsedSeconds = 0;*/
	}
}