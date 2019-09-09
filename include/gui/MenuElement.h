
#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "scenes/Entity.h"
#include "animation/Translatable.h"

namespace ProjectSpace
{
	class MenuElement : public Entity, public sf::Drawable, public Translatable
	{
	public:
		virtual ~MenuElement() {}
	};
}

#endif