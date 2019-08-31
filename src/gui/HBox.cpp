
#include "gui/HBox.h"

#include "utility/Util.h"

namespace ProjectSpace
{
    HBox::HBox(float spacing) : bounds{0, 0, 0, 0}, spacing{spacing}, hidden{false} {}

    HBox::HBox(std::vector<MenuElement *> menuElements, sf::Vector2f position, float spacing)
        : menuElements{ menuElements }, bounds{ position.x, position.y, -1, -1 }, spacing{ spacing },
          hidden{false}
    {
        updateWidth();
        updateHeight();
        updatePositions();
    }

    void HBox::update(sf::Time time)
    {
        if (!hidden)
        {
            for (MenuElement *b : menuElements)
            {
                b->update(time);
            }
        }
    }

    void HBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (!hidden)
        {
            for (MenuElement *m : menuElements)
            {
                target.draw(*m);
            }
        }
    }

    void HBox::setPosition(sf::Vector2f const &position)
    {
        bounds.left = position.x;
        bounds.top = position.y;

        updatePositions();
    }

    void HBox::setPosition(float x, float y)
    {
        bounds.left = x;
        bounds.top = y;

        updatePositions();
    }

    void HBox::move(sf::Vector2f const &by)
    {
        bounds.left += by.x;
        bounds.top += by.y;

        updatePositions();
    }

    void HBox::move(float byX, float byY)
    {
        bounds.left += byX;
        bounds.top += byY;

        updatePositions();
    }

    sf::Vector2f HBox::getPosition() const
    {
        return sf::Vector2f{bounds.left, bounds.top};
    }

    float HBox::getX() const
    {
        return bounds.left;
    }

    float HBox::getY() const
    {
        return bounds.top;
    }

    sf::Vector2f HBox::getSize() const
    {
        return sf::Vector2f{bounds.width, bounds.height};
    }

    float HBox::getWidth() const
    {
        return bounds.width;
    }

    float HBox::getHeight() const
    {
        return bounds.height;
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

    void HBox::addMenuElement(MenuElement *b)
    {
        menuElements.push_back(b);
        updateWidth();
		updateHeight();
		updatePositions();
    }

    void HBox::addMenuElements(std::vector<MenuElement *> menuElements)
    {
        for (MenuElement *b : menuElements)
        {
            this->menuElements.push_back(b);
        }
        updateWidth();
		updateHeight();
		updatePositions();
    }

    void HBox::setSpacing(float spacing)
    {
        this->spacing = spacing;
        updateWidth();
        updatePositions();
    }

    void HBox::updatePositions()
    {
        // Do nothing if HBox is empty.
        if (menuElements.size() == 0)
        {
            return;
        }

        // Position first element at upper left corner of HBox.
		menuElements[0]->setPosition(sf::Vector2f{bounds.left, bounds.top});

        // Nothing else to do if HBox only has 1 Element.
        if (menuElements.size() == 1)
        {
            return;
        }

        // Position every element (except first) at HBox.X and HBox.Y + previousElement.Y + spacing.
        for (int i = 1; i < menuElements.size(); ++i)
        {
            menuElements[i]->setPosition(menuElements[i - 1]->getX() + menuElements[i - 1]->getWidth() + spacing, bounds.top);
        }
    }

    void HBox::updateWidth()
    {
    	float width = 0;
        for (MenuElement const *m : menuElements)
        {
            width += m->getWidth();
        }
        width += (menuElements.size() - 1) * spacing;
        bounds.width = width;
    }

    void HBox::updateHeight()
    {
    	float height = menuElements[0]->getHeight();
        float tempHeight = -1;
        for (MenuElement const *m : menuElements)
        {
            tempHeight = m->getHeight();
            if (height < tempHeight)
            {
                height = tempHeight;
            }
        }
        bounds.height = height;
    }
}