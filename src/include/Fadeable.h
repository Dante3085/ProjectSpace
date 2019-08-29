#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ProjectSpace
{
	class Fadeable
	{
	public:
		virtual ~Fadeable() {}
		virtual void setColor(sf::Color const& color) = 0;
	};
}