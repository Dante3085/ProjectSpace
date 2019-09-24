
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <iostream>
#include <stdio.h>
#include <SFML/Window/Keyboard.hpp>

#include "MenuElement.h"
#include "animation/Animation.h"
#include "animation/AnimatedSprite.h"

namespace ProjectSpace
{
	enum class WritingState
	{
		standard,
		fast,
		immediately
	};

	/**
	 * @brief      A TextBox for displaying Text in the Game.
	 */
	class TextBox : public MenuElement
	{
	public:
		TextBox(std::string texturePath, sf::String str, sf::Vector2f size = sf::Vector2f{ 100, 100 }, sf::Vector2f position = sf::Vector2f{ 0, 0 });

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void update(sf::Time time) override;

		// Textbox Funktionalität
		void setOpacity(int opacity);
		void setPadding(float padding);
		void setSize(float width, float height);
		void setSize(sf::Vector2f const& size);
		void setTextColor(sf::Color color);
		void writeChar(bool withDelay);

		// Override von Translatable Vererbung
		void setPosition(sf::Vector2f const& position) override;
		void setPosition(float x, float y) override;
		void move(sf::Vector2f const& by) override;
		void move(float byX, float byY) override;
		sf::Vector2f getPosition() const override;
		float getX() const override;
		float getY() const override;
		sf::Vector2f getSize() const override;
		float getWidth() const override;
		float getHeight() const override;

	private:

		sf::String originalStr;          // Unchanged text content.
		std::vector<sf::String> wrappedStr;           // originalStr with text-wrapping (Text-wrapping ist die gängige Bezeichnung für automatische Zeilenumbrüche in Text.)
		sf::String writtenStr;           // Text content that is currently being displayed.
		sf::Text text;                   // Drawable text.
		sf::Font font;                   // Font for drawable text.
		sf::Texture texture;             // Background texture.
		sf::RectangleShape rec;          // Background geometry.
		float padding;                   // Distance between drawable text and all 4 sides of the background geometry.
		float elapsedMillis;             // For text writing speed. TODO: Bessere Dokumentation hier.
		int currentCharIndex;  // Index of character in wrappedStr that is about to be written.
		int lineBreakCounter;            // For keeping track of how many lines of text have been written compared to lines of text this TextBox can display.
		bool waitForContinueKey;         // Stop writing text and prompt the user to press the continueKey.
		float charDelay;                 // Time it takes for the next character of the wrappedStr to be displayed.

		// TODO: Calculate charWidth properly. Don't just set a number.
		int charWidth;          // Width of a character in the current font.

		// TODO: Calculate lineHeight properly. Don't just set a number.
		float lineHeight;       // ????

		int absatzPtr;

		Animation cursorAnim;   // Animation of the cursor.
		AnimatedSprite cursor;  // Display to prompt the user for input.

		// TODO: Make this agnostic to input type(Keyboard, Gamepad, ...). New InputSystem will deal with this(see: TODO.md: InputSystem).
		sf::Keyboard::Key continueKey;

		// CharSound
		sf::SoundBuffer soundBuffer;
		sf::Sound charSound;

		WritingState writingState;
		
	};
}

#endif
