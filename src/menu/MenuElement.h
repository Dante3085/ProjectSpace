
#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

#include <SFML/Graphics/Drawable.hpp>

#include "../game/Entity.h"

namespace ProjectSpace
{
	class MenuElement : public Entity, public sf::Drawable
	{
	public:
		virtual ~MenuElement() {}

		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;
		virtual sf::Vector2f getPosition() const = 0;
		virtual void setPosition(float x, float y) = 0;
		virtual void setPosition(sf::Vector2f v) = 0;
		virtual void move(float x, float y) = 0;
		virtual void move(sf::Vector2f v) = 0;

	};
}

#endif