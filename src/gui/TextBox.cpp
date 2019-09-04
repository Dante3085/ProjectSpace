
#include "gui/TextBox.h"
#include "utility/Util.h"
#include <iostream>

namespace ProjectSpace
{
	TextBox::TextBox(std::string texturePath, sf::String str, sf::Vector2f size, sf::Vector2f position)
		: originalStr{str}, str{ str }, writtenStr{ "" }, position{ position }, padding{ 0 }, elapsedMillis{ 0 }, currentPos{ 0 }, 
		umbruchZaehler{ 0 }, waitFlag{ false }, charDelay{10}, cursorAnim{ "rsrc/cursor.png", 0.5f }, 
		cursor{ sf::Vector2f{2000, 300} }, continueKey{sf::Keyboard::Space}, charWidth{25}, lineHeight{36.5}
	{
		texture.loadFromFile(texturePath);
		rec.setTexture(&texture);
		rec.setSize(size);
		rec.setOutlineColor(sf::Color(255, 0, 0, 255));

		sf::Color c = rec.getFillColor();
		c.a = 100;
		rec.setFillColor(c);

		font.loadFromFile("rsrc/fonts/joystix_monospace.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color(0, 255, 190, 255));

		//zeilenanzahl =~ size / 36,5
		lineBreaker(this->str, ((size.x-padding) / charWidth));
		text.setString(writtenStr);

		rec.setPosition(position);
		text.setPosition(position);

		sf::Vector2f textPosition = position;
		textPosition.x += padding;
		textPosition.y += padding;
		text.setPosition(textPosition);

		cursorAnim.setAnimation({ {0, 0, 5, 1}, {5, 0, 5, 1}, {10, 0, 5, 1}, {15, 0, 5, 1} }, 0.5f);
		cursor.addAnimation(EAnimation::IDLE, &cursorAnim);
		cursor.setAnimation(EAnimation::IDLE);
		cursor.setScale(10, 10);
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rec);
		target.draw(text);

		if (waitFlag)
		{
			target.draw(cursor);
		}
	}

	void TextBox::update(sf::Time time)
	{
		elapsedMillis += time.asMilliseconds();

		if (waitFlag) {
			cursor.update(time);
			if (sf::Keyboard::isKeyPressed(continueKey))
			{
				waitFlag = false;
			}
		}
		else {
			if (elapsedMillis > charDelay && currentPos < str.getSize()) {
				elapsedMillis = 0;
				if (str[currentPos] == '\n') ++umbruchZaehler;
				if (umbruchZaehler >= ((rec.getSize().y-padding) / lineHeight) - 1) {
					umbruchZaehler = 0;
					writtenStr = "";
					currentPos++;
					waitFlag = true;

					sf::Vector2f cursorPos{ text.findCharacterPos(writtenStr.getSize() - 1) };
					cursorPos.y += text.getCharacterSize();
					cursor.setPosition(cursorPos);
				}
				else {
					writtenStr += str[currentPos++];
					text.setString(writtenStr);
				}
			}
		}
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

		str = originalStr;
		text.setPosition(position.x + padding, position.y + padding);
		lineBreaker(str, ((rec.getSize().x - padding) / charWidth));

		sf::Vector2f textPosition = rec.getPosition();
		textPosition.x += padding;
		textPosition.y += padding;
		text.setPosition(textPosition);
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
