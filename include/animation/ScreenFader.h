
#ifndef SCREEN_FADER_H
#define SCREEN_FADER_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "Fadeable.h"

namespace ProjectSpace
{
	class ScreenFader : public Fadeable
	{
	public:
		ScreenFader(sf::Vector2f const& screenSize);
		ScreenFader(float screenWidth, float screenHeight);

		void setColor(sf::Color const& color) override;

	private:
		sf::RectangleShape overlay;
	};
}

#endif