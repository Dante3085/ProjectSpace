
#include "FpsCounter.h"

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

	void FpsCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!hide)
		{
			target.draw(text);
		}
	}

	sf::Vector2f FpsCounter::getPosition() const
	{
		return position;
	}

	float FpsCounter::getWidth() const
	{
		return text.getGlobalBounds().width;
	}

	float FpsCounter::getHeight() const
	{
		return text.getGlobalBounds().height;
	}

	void FpsCounter::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
		text.setPosition(position);
	}

	void FpsCounter::setPosition(sf::Vector2f v)
	{
		position = v;
		text.setPosition(position);
	}

	void FpsCounter::move(float x, float y)
	{
		position.x += x;
		position.y += y;
		text.move(position);
	}

	void FpsCounter::move(sf::Vector2f v)
	{
		position += v;
		text.move(position);
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