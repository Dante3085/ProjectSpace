
#include "gui/TextBox.h"

#include "utility/Util.h"

namespace ProjectSpace
{
	int TextBox::numInstances = 0;
#define m 4
	TextBox::TextBox(std::string texturePath, sf::String str, sf::Vector2f size, sf::Vector2f position)
		: originalStr{ str }, 
		wrappedStr{ str }, 
		writtenStr{ "" }, 
		padding{ 50 }, 
		elapsedMillis{ 0 }, 
		currentCharIndex{ 0 },
		lineBreakCounter{ 0 }, 
		waitForContinueKey{ false }, 
		charDelay{ 100 }, 
		cursorAnim{ "rsrc/spritesheets/cursor.png", 0.5f },
		cursor{ sf::Vector2f{0, 0} }, 
		charWidth{ 25 }, 
		lineHeight{ 36.5 },
		inputContext{"include/input/contexts/TextBoxContext.txt"},
		inputManager{&InputManager::getInstance()}
	{
		// Initialize this Textbox's background.
		texture.loadFromFile(texturePath);
		rec.setTexture(&texture);
		rec.setSize(size);
		rec.setOutlineColor(sf::Color(255, 0, 0, 255));
		rec.setPosition(position);
		setOpacity(100);

		// Initialize this Textbox's text.
		font.loadFromFile("rsrc/fonts/joystix_monospace.ttf");
		text.setFont(font);

		//// Get width of A Character glyph(Glyph is a visual representation of a character).
		//// Doesn't work
		//charWidth = font.getGlyph(65, text.getCharacterSize(), false).bounds.width;

		text.setFillColor(sf::Color(255, 255, 255, 255));
		//zeilenanzahl =~ size / 36,5
		text.setString(writtenStr);
		text.setPosition(position.x + padding, position.y + padding);
		wrappedStr = addTextWrapping(this->originalStr, (size.x - 2 * padding) / charWidth, (rec.getSize().y - 2 * padding), lineHeight);
		// Initialize this Textbox's cursor.
		cursorAnim.setAnimation({ {0, 0, 5, 1}, {5, 0, 5, 1}, {10, 0, 5, 1}, {15, 0, 5, 1} }, 0.5f);
		cursor.addAnimation(EAnimation::IDLE, &cursorAnim);
		cursor.setAnimation(EAnimation::IDLE);
		cursor.setScale(6, 6);

		// charSound
		soundBuffer.loadFromFile("rsrc/audio/sfx/phoenixWright/sfx-blipmale.wav");
		charSound.setBuffer(soundBuffer);

		inputContext.setPredicate([]()
			{
				return true;
			});
		std::string inputContextName = "TextBox";
		inputContextName.append(std::to_string(numInstances++));
		inputManager->registerInputContext(inputContextName, &inputContext);
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rec);
		target.draw(text);

		if (waitForContinueKey)
		{	
			if (absatzPtr < wrappedStr.size()-1)
			{
				target.draw(cursor);
			}
		}
	}

	void TextBox::writeChar(bool withDelay)
	{
		if (((!withDelay) || (elapsedMillis > charDelay)) && currentCharIndex < wrappedStr[absatzPtr].getSize())
		{
			if (charSound.getStatus() != sf::Sound::SoundSource::Status::Playing)
			{
				charSound.play();
			}

			elapsedMillis = 0;

			// Every line of this TextBox is full of text.
			writtenStr += wrappedStr[absatzPtr][currentCharIndex++];
			text.setString(writtenStr);
		}
		else
		{
			if (currentCharIndex >= wrappedStr[absatzPtr].getSize())
			{
				writtenStr = "";
				if (absatzPtr < wrappedStr.size())
				{
					waitForContinueKey = true;
				}
				else
				{
					waitForContinueKey = false;
				}
				currentCharIndex = 0;
				//++absatzPtr;
				sf::Vector2f cursorPos{ text.findCharacterPos(writtenStr.getSize() - 1) };

				// Try to roughly position the cursor at 80 percent of the Character's height.
				// So roughly at the Character's foot.
				cursorPos.y += text.getCharacterSize() * 0.8f;
				cursor.setPosition(cursorPos);
			}
		}

	}

	void TextBox::update(sf::Time time)
	{

		// TODO: Make it possible to show all the text with a single button press.
		if (absatzPtr >= wrappedStr.size())
		{	
			waitForContinueKey = false;
			return;
		}
		elapsedMillis += time.asMilliseconds();

		if (inputContext.isStateOn(State::TEXTBOX_FAST))
		{
			writingState = WritingState::fast;
		}
		else
		{
			writingState = WritingState::standard;
		}


		if (waitForContinueKey)
		{
			cursor.update(time);

			if (inputContext.hasActionFired(Action::TEXTBOX_CONTINUE))
			{
				++absatzPtr;
				waitForContinueKey = false;
			}
		}
		else
		{	
			/*if (inputContext.hasActionFired(Action::TEXTBOX_IMMEDIATLY))
			{
				writingState = WritingState::immediately;
			}*/
			//writingState = WritingState::immediately;
			switch (writingState)
			{
			case WritingState::standard:
				writeChar(true);
				break;
			case WritingState::fast:
				writeChar(false);
				break;
			case WritingState::immediately:
				writtenStr = wrappedStr[absatzPtr];
				text.setString(writtenStr);
				if (absatzPtr < (wrappedStr.size() - 1))
				{
					waitForContinueKey = true;
					sf::Vector2f cursorPos{ text.findCharacterPos(writtenStr.getSize() - 1) };
					// Try to roughly position the cursor at 80 percent of the Character's height.
					// So roughly at the Character's foot.
					cursorPos.y += text.getCharacterSize() * 0.8f;
					cursor.setPosition(cursorPos);
				}
				break;
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

		wrappedStr = addTextWrapping(this->originalStr, (rec.getSize().x - 2 * padding) / charWidth, (rec.getSize().y - 2 * padding), lineHeight);//??????originalStr;
		//??????addLineWrapping(wrappedStr, ((rec.getSize().x - 2*padding) / charWidth));

		text.setPosition(rec.getPosition() + padding);

		// TODO: Currently padding does not leave the same amount of space on all 4 sides.
	}

	void TextBox::setPosition(float x, float y)
	{
		rec.setPosition(x, y);
		text.setPosition(x + padding, y + padding);
	}

	void TextBox::setPosition(sf::Vector2f const& position)
	{
		rec.setPosition(position);
		text.setPosition(position + padding);
	}

	void TextBox::move(float x, float y)
	{
		rec.move(x, y);
		text.move(x, y);
	}

	void TextBox::move(sf::Vector2f const& by)
	{
		rec.move(by);
		text.move(by);
	}

	void TextBox::setSize(float width, float height)
	{
		rec.setSize(sf::Vector2f(width, height));

		// TODO: Reparse String so that the Text fits the new size.
	}

	void TextBox::setSize(sf::Vector2f const& size)
	{
		rec.setSize(size);

		// TODO: Reparse String so that the Text fits the new size.
	}

	void TextBox::setTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	sf::Vector2f TextBox::getPosition() const
	{
		return rec.getPosition();
	}

	float TextBox::getWidth() const
	{
		return rec.getSize().x;
	}

	float TextBox::getHeight() const
	{
		return rec.getSize().y;
	}

	float TextBox::getX() const
	{
		return rec.getPosition().x;
	};

	float TextBox::getY() const
	{
		return rec.getPosition().y;
	};

	sf::Vector2f TextBox::getSize() const
	{
		return rec.getSize();
	};
}
