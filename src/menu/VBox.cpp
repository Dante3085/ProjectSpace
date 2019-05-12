
#include "VBox.h"

namespace ProjectSpace
{
	VBox::VBox(float spacing) : position{0, 0}, spacing{spacing}, needsUpdate{true}, hidden{false} {}

	VBox::VBox(std::vector<MenuElement*> menuElements, sf::Vector2f position, float spacing) 
	: menuElements{menuElements}, position{position}, spacing{spacing}, needsUpdate{true}, hidden{false} {}

	void VBox::update(sf::Time time)
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

				// Do nothing if VBox is empty.
			if (menuElements.size() == 0)
			{
				return;
			}

            	// Position first element at upper left corner of VBox.
			menuElements[0]->setPosition(position);

				// Nothing else to do if Vbox only has 1 Element.
			if (menuElements.size() == 1)
			{
				return;
			}

            	// Position every element (except first) at VBox.position + previousElement.Y + spacing.
			for (int i = 1; i < menuElements.size(); ++i)
			{
				menuElements[i]->setPosition(position.x, menuElements[i - 1]->getPosition().y + menuElements[i - 1]->getHeight() + spacing);
			}
		}
	}

	void VBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!hidden)
		{
			for (MenuElement* b : menuElements)
			{
				target.draw(*b);
			}
		}
	}

	void VBox::show()
	{
		hidden = false;
	}

	void VBox::hide()
	{
		hidden = true;
	}

	bool VBox::isHidden()
	{
		return hidden;
	}

	void VBox::setNeedsUpdate()
	{
		needsUpdate = true;
	}

	void VBox::addMenuElement(MenuElement* b)
	{
		menuElements.push_back(b);
	}

	void VBox::addMenuElements(std::vector<MenuElement*> menuElements)
	{
		for (MenuElement* b : menuElements)
		{
			this->menuElements.push_back(b);
		}
	}

	void VBox::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;

		needsUpdate = true;
	}

	void VBox::setPosition(sf::Vector2f v)
	{
		position = v;

		needsUpdate = true;
	}

	void VBox::move(float x, float y)
	{
		position.x += x;
		position.y += y;

		needsUpdate = true;
	}

	void VBox::move(sf::Vector2f v)
	{
		position += v;
		needsUpdate = true;
	}

	void VBox::setSpacing(float spacing)
	{
		this->spacing = spacing;
	}

	float VBox::getWidth() const
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

	float VBox::getHeight() const
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

	sf::Vector2f VBox::getPosition() const
	{
		return position;
	}
}