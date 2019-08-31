
#include "VBox.h"
#include "Util.h"

namespace ProjectSpace
{
    VBox::VBox(float spacing) : bounds{0, 0, 0, 0}, spacing{spacing}, hidden{false} 
	{}

    VBox::VBox(std::vector<MenuElement *> menuElements, sf::Vector2f position, float spacing)
        : menuElements{menuElements}, bounds{position.x, position.y, -1, -1}, spacing{spacing}, 
		hidden{false} 
	{
		updateWidth();
		updateHeight();
		updatePositions();
	}

    void VBox::update(sf::Time time)
    {
        if (!hidden)
        {
            for (MenuElement *b : menuElements)
            {
                b->update(time);
            }
        }
    }

    void VBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (!hidden)
        {
            for (MenuElement *m : menuElements)
            {
                target.draw(*m);
            }
        }
    }

    void VBox::setPosition(sf::Vector2f const &position)
    {
		bounds.left = position.x;
		bounds.top = position.y;

		updatePositions();
    }

    void VBox::setPosition(float x, float y)
    {
        bounds.left = x;
        bounds.top = y;

		updatePositions();
    }

    void VBox::move(sf::Vector2f const &by)
    {
		bounds.left += by.x;
		bounds.top += by.y;

		updatePositions();
    }

    void VBox::move(float byX, float byY)
    {
        bounds.left += byX;
        bounds.top += byY;

		updatePositions();
    }

    sf::Vector2f VBox::getPosition() const
    {
		return sf::Vector2f{bounds.left, bounds.top};
    }

    float VBox::getX() const
    {
		return bounds.left;
    }

    float VBox::getY() const
    {
		return bounds.top;
    }

    sf::Vector2f VBox::getSize() const
    {
    	return sf::Vector2f{bounds.width, bounds.height};
    }

    float VBox::getWidth() const
    {
		return bounds.width;
    }

    float VBox::getHeight() const
    {
		return bounds.height;
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

    void VBox::addMenuElement(MenuElement *m)
    {
        menuElements.push_back(m);
		updateWidth();
		updateHeight();
		updatePositions();
    }

    void VBox::addMenuElements(std::vector<MenuElement *> menuElements)
    {
        for (MenuElement *b : menuElements)
        {
            this->menuElements.push_back(b);
		}
		updateWidth();
		updateHeight();
		updatePositions();
    }

    void VBox::setSpacing(float spacing)
    {
        this->spacing = spacing;
		updateHeight();
		updatePositions();
    }

	void VBox::updatePositions()
	{
		// Do nothing if VBox is empty.
		if (menuElements.size() == 0)
		{
			return;
		}

		// Position first element at upper left corner of VBox.
		menuElements[0]->setPosition(sf::Vector2f{ bounds.left, bounds.top });

		// Nothing else to do if Vbox only has 1 Element.
		if (menuElements.size() == 1)
		{
			return;
		}

		// Position every element (except first) at VBox.position + previousElement.Y + spacing.
		for (int i = 1; i < menuElements.size(); ++i)
		{
			menuElements[i]->setPosition(bounds.left, menuElements[i - 1]->getY() + menuElements[i - 1]->getHeight() + spacing);
		}
	}

	void VBox::updateWidth()
	{
		float width = menuElements[0]->getWidth();
		float tempWidth = -1;
		for (MenuElement const* m : menuElements)
		{
			tempWidth = m->getWidth();
			if (width < tempWidth)
			{
				width = tempWidth;
			}
		}
		bounds.width = width;
	}

	void VBox::updateHeight()
	{
		float height = 0;
		for (MenuElement const* m : menuElements)
		{
			height += m->getHeight();
		}
		height += (menuElements.size() - 1) * spacing;
		bounds.height = height;
	}
}