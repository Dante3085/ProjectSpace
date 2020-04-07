
#include "animation/ScreenFader.h"

namespace ProjectSpace
{
	ScreenFader::ScreenFader(sf::Vector2f const& screenSize)
		: overlay{screenSize}
	{
		overlay.setPosition(0, 0);
	}

	ScreenFader::ScreenFader(float screenWidth, float screenHeight)
		: ScreenFader{sf::Vector2f{screenWidth, screenHeight}}
	{}

	void ScreenFader::setColor(sf::Color const& color)
	{
		overlay.setFillColor(color);
	}
}