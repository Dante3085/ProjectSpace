
#include "FadeAnimation.h"

namespace ProjectSpace
{
	FadeAnimation::FadeAnimation(sf::Sprite* sprite, float duration) 
	: sprite{sprite}, color{255, 255, 255, 255}, delay{duration / 255}, amount{-255.f / duration}, elapsedSeconds{0}, 
	doUpdate{false} {}

	void FadeAnimation::update(sf::Time time)
	{
		if (doUpdate)
		{
			if (color.a > 0)
			{
				color.a -= amount;
				sprite->setColor(color);
			}
			elapsedSeconds += time.asSeconds();
			std::cout << "test" << std::endl;
		}
	}

	void FadeAnimation::start()
	{
		doUpdate = true;
	}

	void FadeAnimation::refresh()
	{
		color.a = 255;
		sprite->setColor(color);
		elapsedSeconds = 0;
	}
}