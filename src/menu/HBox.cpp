
#include "HBox.h"

namespace ProjectSpace
{
	HBox::HBox(float spacing) : position{0, 0}, spacing{spacing}, needsUpdate{true}, hidden{false} {}

	HBox::HBox(std::vector<MenuElement*> menuElements, sf::Vector2f position, float spacing) 
	: menuElements{menuElements}, position{position}, spacing{spacing}, needsUpdate{true} {}

	void HBox::update(sf::Time time)
	{
		if (!hidden)
		{
			for (MenuElement* b : menuElements)
			{
				b->update(time);
			}
		}

		if (needsUpdate)
		{
			needsUpdate = false;

				// Do nothing if HBox is empty.
			if (menuElements.size() == 0)
			{
				return;
			}

            	// Position first element at upper left corner of HBox.
			menuElements[0]->setPosition(position);

				// Nothing else to do if HBox only has 1 Element.
			if (menuElements.size() == 1)
			{
				return;
			}

            	// Position every element (except first) at HBox.X and HBox.Y + previousElement.Y + spacing.
			for (int i = 1; i < menuElements.size(); ++i)
			{
				menuElements[i]->setPosition(menuElements[i - 1]->getPosition().x + menuElements[i - 1]->getWidth() + spacing, position.y);
			}
		}
	}

	void HBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!hidden)
		{
			for (MenuElement* b : menuElements)
			{
				target.draw(*b);
			}
		}
	}

	void HBox::show()
	{
		hidden = false;
	}

	void HBox::hide()
	{
		hidden = true;
	}

	bool HBox::isHidden()
	{
		return hidden;
	}

	void HBox::setNeedsUpdate()
	{
		needsUpdate = true;
	}

	void HBox::addMenuElement(MenuElement* b)
	{
		menuElements.push_back(b);
	}

	void HBox::addMenuElements(std::vector<MenuElement*> menuElements)
	{
		for (MenuElement* b : menuElements)
		{
			this->menuElements.push_back(b);
		}
	}

	void HBox::setSpacing(float spacing)
	{
		this->spacing = spacing;
	}

	void HBox::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;

		needsUpdate = true;
	}

	void HBox::setPosition(sf::Vector2f v)
	{
		position = v;

		needsUpdate = true;
	}

	void HBox::move(float x, float y)
	{
		position.x += x;
		position.y += y;

		needsUpdate = true;
	}

	void HBox::move(sf::Vector2f v)
	{
		position += v;
		needsUpdate = true;
	}

	float HBox::getWidth() const
	{
		float width = menuElements[0]->getWidth();
		for (MenuElement* m : menuElements)
		{
			if (width < m->getWidth())
			{
				width = m->getWidth();
			}
		}
		return width;
	}

	float HBox::getHeight() const
	{
		float height = menuElements[0]->getHeight();
		for (MenuElement* m : menuElements)
		{
			if (height < m->getHeight())
			{
				height = m->getHeight();
			}
		}
		return height;
	}

	sf::Vector2f HBox::getPosition() const
	{
		return position;
	}
}