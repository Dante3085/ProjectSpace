#pragma once

#include "MenuElement.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <iostream>

namespace ProjectSpace
{
	class MenuGroup : public MenuElement
	{
	public:
		MenuGroup(sf::Vector2f const& position) : position{position} {}

		void update(sf::Time time) override
		{
			for (MenuElement* m : menuElements)
			{
				m->update(time);
			}
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			for (MenuElement* m : menuElements)
			{
				target.draw(*m);
			}
		}

		void addMenuElement(MenuElement* m)
		{
			for (MenuElement* m2 : menuElements)
			{
				if (m == m2)
				{
					std::cout << "@MenuGroup::addMenuElement(): This MenuGroup already contains given MenuElement." << std::endl;
					return;
				}
			}
			menuElements.push_back(m);

			m->setPosition(position + m->getPosition());
		}

		void removeMenuElement(MenuElement* m)
		{
			for (std::vector<MenuElement*>::iterator it = menuElements.begin(); it != menuElements.end(); ++it)
			{
				if (m == *it)
				{
					menuElements.erase(it);
					return;
				}
			}
			std::cout << "@MenuGroup::removeMenuElement(): This MenuGroup does not contain the given MenuElement." << std::endl;
		}

		void removeAt(int index)
		{
			if (index < 0 || index >= menuElements.size())
			{
				std::cout << "@MenuGroup::removeAt(" << index << "): Given index is invalid." << std::endl;
				return;
			}
			menuElements.erase(menuElements.begin() + index);
		}

		float getWidth() const override { return -1; }
		float getHeight() const override { return -1; }
		sf::Vector2f getPosition() const override { return position; }

		void setPosition(float x, float y) override
		{
			sf::Vector2f shiftVector{ x - position.x, y - position.y };
			position.x = x;
			position.y = y;

			for (MenuElement* m : menuElements)
			{
				m->move(shiftVector);
			}
		}

		void setPosition(sf::Vector2f v) override
		{
			sf::Vector2f shiftVector{ v - position };
			position = v;

			for (MenuElement* m : menuElements)
			{
				m->move(shiftVector);
			}
		}

		virtual void move(float x, float y) override
		{
			position.x += x;
			position.y += y;

			for (MenuElement* m : menuElements)
			{
				m->move(x, y);
			}
		}

		virtual void move(sf::Vector2f v) override
		{
			position += v;

			for (MenuElement* m : menuElements)
			{
				m->move(v);
			}
		}

	private:
		std::vector<MenuElement*> menuElements;
		sf::Vector2f position;
	};
}