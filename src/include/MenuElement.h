
#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Entity.h"
#include "Translatable.h"

namespace ProjectSpace
{
	class MenuElement : public Entity, public sf::Drawable, public Translatable
	{
	public:
		virtual ~MenuElement() {}
	};
}

#endif