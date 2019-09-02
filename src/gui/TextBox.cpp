
#include "gui/TextBox.h"
#include "utility/Util.h"
#include <iostream>

namespace ProjectSpace
{
	TextBox::TextBox(std::string texturePath, sf::String str, sf::Vector2f size, sf::Vector2f position)
		: str{ str }, writtenStr{ "" }, position{ position }, padding{ 0 }, elapsedMillis{ 0 }, currentPos{ 0 }
	{
		texture.loadFromFile(texturePath);
		rec.setTexture(&texture);
		rec.setSize(size);

		font.loadFromFile("rsrc/fonts/arial.ttf");
		text.setFont(font);
		parseString(this->str, 20, 10);
		text.setString(writtenStr);
		rec.setPosition(position);
		text.setPosition(position);
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rec);
		target.draw(text);
	}

	void TextBox::update(sf::Time time)
	{	

		elapsedMillis += time.asMilliseconds();
		if (elapsedMillis > 20 && currentPos<str.getSize()) {
			elapsedMillis = 0;
			writtenStr += str[currentPos++];
			text.setString(writtenStr);
		}
		//	// TODO(moritz):
	}

	void TextBox::setOpacity(int opacity)
	{
		sf::Color color = rec.getFillColor();
		color.a = opacity;
		rec.setFillColor(color);
	}

	void TextBox::setPadding(float padding)
	{
		this->padding = padding;
		text.setPosition(position.x + padding, position.y + padding);
		parseText();
	}

	void TextBox::parseText()
	{
		float const recWidth = rec.getGlobalBounds().width; 
		for (int i = 0; i < text.getString().getSize(); ++i)
		{
			if (text.findCharacterPos(i).x > recWidth)
			{
				auto str = text.getString();
				str.insert(i, "\n");
				text.setString(str);
			}
		}
	}

	void TextBox::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;

		rec.setPosition(position);
		text.setPosition(position);
	}

	void TextBox::setPosition(sf::Vector2f const& position)
	{
		this->position = position;
		rec.setPosition(position);
		text.setPosition(position);
	}

	void TextBox::move(float x, float y)
	{
		position.x += x;
		position.y += y;

		rec.setPosition(position);
		text.setPosition(position);
	}

	void TextBox::move(sf::Vector2f const& by)
	{
		position += by;

		rec.setPosition(position);
		text.setPosition(position);
	}

	void TextBox::setSize(float width, float height)
	{
		rec.setSize(sf::Vector2f(width, height));
	}

	void TextBox::setSize(sf::Vector2f const& size)
	{
		rec.setSize(size);
	}

	sf::Vector2f TextBox::getPosition() const
	{
		return position;
	}

	float TextBox::getWidth() const
	{
		return rec.getGlobalBounds().width;
	}

	float TextBox::getHeight() const
	{
		return rec.getGlobalBounds().height;
	}
	float TextBox::getX() const {
		return rec.getPosition().x;
	};
	float TextBox::getY() const {
		return rec.getPosition().y;
	};
	sf::Vector2f TextBox::getSize() const {
		return rec.getSize();
	};
}