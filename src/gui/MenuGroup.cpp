
#include "gui/MenuGroup.h"

#include "utility/Util.h"
#include "utility/Log.h"

namespace ProjectSpace
{
	MenuGroup::MenuGroup() 
		: menuElements{}, 
		bounds{} 
	{

	}

    MenuGroup::MenuGroup(std::vector<MenuElement*>& menuElements)
		: menuElements{ menuElements }, 
		bounds{}
    {
		// Figure out bounds(x/left, y/top, width, height) of MenuGroup given by given MenuElements.
		// I know this all could probably be done in a single iteration over all MenuElements,
		// but for clarities sake I am doing it like this for now.
		float temp = -1;

		float left = menuElements[0]->getX();
		float top = menuElements[0]->getY();
		
		for (MenuElement const* m : menuElements)
		{
			temp = m->getX();
			if (left > temp)
			{
				left = temp;
			}

			temp = m->getY();
			if (top > temp)
			{
				top = temp;
			}
		}

		float right = menuElements[0]->getX() + menuElements[0]->getWidth();
		float bottom = menuElements[0]->getY() + menuElements[0]->getHeight();

		temp = -1;
		for (MenuElement const* m : menuElements)
		{
			temp = m->getX() + m->getWidth();
			if (right < temp)
			{
				right = temp;
			}

			temp = m->getY() + m->getHeight();
			if (bottom < temp)
			{
				bottom = temp;
			}
		}

		bounds.left = left;
		bounds.top = top;
		bounds.width = right - left;
		bounds.height = bottom - top;
    }

    void MenuGroup::update(sf::Time time)
    {
        for (MenuElement *m : menuElements)
        {
            m->update(time);
        }
    }

    void MenuGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (MenuElement const *m : menuElements)
        {
            target.draw(*m);
        }
    }

    void MenuGroup::setPosition(sf::Vector2f const &position)
    {
		sf::Vector2f shiftVector{ position - sf::Vector2f{bounds.left, bounds.top} };
		bounds.left = position.x;
		bounds.top = position.y;

        for (MenuElement *m : menuElements)
        {
            m->move(shiftVector);
        }
    }

    void MenuGroup::setPosition(float x, float y)
    {
        sf::Vector2f shiftVector{ x - bounds.left, y - bounds.top };
        bounds.left = x;
        bounds.top = y;

        for (MenuElement *m : menuElements)
        {
            m->move(shiftVector);
        }
    }

    void MenuGroup::move(sf::Vector2f const &by)
    {
		bounds.left += by.x;
		bounds.top += by.y;

        for (MenuElement *m : menuElements)
        {
            m->move(by);
        }
    }

    void MenuGroup::move(float byX, float byY)
    {
        bounds.left += byX;
        bounds.top += byY;

        for (MenuElement *m : menuElements)
        {
            m->move(byX, byY);
        }
    }

    sf::Vector2f MenuGroup::getPosition() const
    {
		return sf::Vector2f{bounds.left, bounds.top};
    }

    float MenuGroup::getX() const
    {
		return bounds.left;
    }

    float MenuGroup::getY() const
    {
		return bounds.top;
    }

    sf::Vector2f MenuGroup::getSize() const
    {
        return sf::Vector2f{getWidth(), getHeight()};
    }

    float MenuGroup::getWidth() const
    {
		return bounds.width;
    }

    float MenuGroup::getHeight() const
    {
		return bounds.height;
    }

    void MenuGroup::addMenuElement(MenuElement *m)
    {
        for (MenuElement *m2 : menuElements)
        {
            if (m == m2)
            {
				Log::getInstance().defaultLog("This MenuGroup already contains the given MenuElement!", ll::WARNING);
                return;
            }
        }
        menuElements.push_back(m);

		// Figure out bounds of menuElement. Should maybe be in MenuElement or Translatable.
		sf::Vector2f mTopLeft = m->getPosition();
		sf::Vector2f mTopRight = m->getPosition() + sf::Vector2f{ m->getWidth(), 0 };
		sf::Vector2f mBottomRight = mTopRight + sf::Vector2f{0, m->getHeight()};
		sf::Vector2f mBottomLeft = mTopLeft + sf::Vector2f{ 0, m->getHeight() };

		// left of menu group
		if (mTopLeft.x < bounds.left)
		{
			float rightMost = bounds.left + bounds.width;
			bounds.left = mTopLeft.x;
			bounds.width = rightMost - bounds.left;
		}

		// right of menu group
		if (mTopRight.x > (bounds.left + bounds.width))
		{
			bounds.width = mTopRight.x - bounds.left;
		}

		// above menu group
		if (mTopLeft.y < bounds.top)
		{
			float downMost = bounds.top + bounds.height;
			bounds.top = mTopLeft.y;
			bounds.height = downMost - bounds.top;
		}

		// below menu group
		if (mTopLeft.y > (bounds.top + bounds.height))
		{
			bounds.height = mBottomLeft.y - bounds.top;
		}
    }

    void MenuGroup::removeMenuElement(MenuElement *m)
    {
        for (std::vector<MenuElement *>::iterator it = menuElements.begin(); it != menuElements.end(); ++it)
        {
            if (m == *it)
            {
                menuElements.erase(it);
                return;
            }
        }

		// TODO: Update bounds

		Log::getInstance().defaultLog("This MenuGroup does not contain the given MenuElement!", ll::WARNING);
    }

    void MenuGroup::removeAt(int index)
    {
        if (index < 0 || index >= menuElements.size())
        {
			std::string msg = "Given index '";
			msg.append(std::to_string(index));
			msg.append("' is invalid!");
			Log::getInstance().defaultLog(msg, ll::ERR);
            return;
        }
        menuElements.erase(menuElements.begin() + index);

		// TODO: update bounds

    }
}