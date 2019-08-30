#pragma once

#include "MenuElement.h"
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace ProjectSpace
{
	class MenuGroup : public MenuElement
	{
	public:
		MenuGroup();
		MenuGroup(std::vector<MenuElement*>& menuElements);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setPosition(sf::Vector2f const& position) override;
		void setPosition(float x, float y) override;
		void move(sf::Vector2f const& by) override;
		void move(float byX, float byY) override;
		sf::Vector2f getPosition() const override;
		float getX() const override;
		float getY() const override;
		sf::Vector2f getSize() const override;
		float getWidth() const override;
		float getHeight() const override;

		void addMenuElement(MenuElement* m);
		void removeMenuElement(MenuElement* m);
		void removeAt(int index);

	private:
		std::vector<MenuElement*> menuElements;
		sf::FloatRect bounds;
	};
}