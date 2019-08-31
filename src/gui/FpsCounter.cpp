
#include "gui/FpsCounter.h"

namespace ProjectSpace
{

    FpsCounter::FpsCounter(std::string fontPath, int x, int y)
        : hide{false}
    {
        font.loadFromFile(fontPath);
        text.setFont(font);
        text.setPosition(x, y);
    }

    void FpsCounter::update(sf::Time time)
    {
        if (!hide)
        {
            str = "fps: ";
            str.append(std::to_string(1.0f / time.asSeconds()));
            text.setString(str);
        }
    }

    void FpsCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (!hide)
        {
            target.draw(text);
        }
    }

    void FpsCounter::setPosition(sf::Vector2f const& position)
    {
        this->position = position;
        text.setPosition(position);
    }

    void FpsCounter::setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
        text.setPosition(position);
    }

    void FpsCounter::move(sf::Vector2f const& by)
    {
        position += by;
        text.move(by);
    }

    void FpsCounter::move(float byX, float byY)
    {
        position.x += byX;
        position.y += byY;
        text.move(byX, byY);
    }

    sf::Vector2f FpsCounter::getPosition() const
    {
        return position;
    }

    float FpsCounter::getX() const
    {
        return position.x;
    }

    float FpsCounter::getY() const
    {
        return position.y;
    }

    sf::Vector2f FpsCounter::getSize() const
    {
		sf::FloatRect textBounds = text.getGlobalBounds();
		return sf::Vector2f{ textBounds.width, textBounds.height };
    }

    float FpsCounter::getWidth() const
    {
        return text.getGlobalBounds().width;
    }

    float FpsCounter::getHeight() const
    {
        return text.getGlobalBounds().height;
    }

    void FpsCounter::setHide(bool hide)
    {
        this->hide = hide;
    }
    bool FpsCounter::isHidden()
    {
        return hide;
    }
}