
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>

#include "Entity.h"
#include "MenuElement.h"

namespace ProjectSpace
{
	/**
	 * @brief      Represents a GUI Button for Menus.
	 */
	class Button : public MenuElement
	{
	public:
		
		Button(std::function<void()> onPressed, sf::Window const& window, std::string string = "NONE");
		Button(sf::Window const& window, std::string string = "NONE");

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setPosition(sf::Vector2f const& position) override;
		void setPosition(float x, float y) override;
		void move(sf::Vector2f const& by);
		void move(float byX, float byY) override;
		sf::Vector2f getPosition() const override;
		float getX() const override;
		float getY() const override;
		sf::Vector2f getSize() const;
		float getWidth() const override;
		float getHeight() const override;

		void setOnPressed(std::function<void()> onPressed);
		void setOnSelected(std::function<void()> onSelected);
		void setOnUnselected(std::function<void()> onUnselected);
		void setFillColor(sf::Color color);
		void setOpacity(int opacity);
		void setSize(float width, float height);
		void setSize(sf::Vector2f const& size);
		void select() const;
		void unselect() const;
		void press() const;

	private:
		bool leftMouseDown;						// Stores whether or not the LeftMouseButton is currently down.
		bool previousLeftMouseDown;   			// Stores whether or not LeftMouseButton was clicked in the last update call.
		bool mouseOnButton;						// Stores whether or not Mouse is on the Button in the current update call.
		bool previousMouseOnButton;				// Stores whether or not Mouse was on the Button in the previous update call.
		sf::Window const& window; 	  			// Reference to Game's window. For Mouse stuff.
		sf::RectangleShape rectangle; 			// The Button's shape.
		sf::Text text; 				  			// Text displayed on Button.
		sf::Font font; 				  			// Font for Button Text.
		std::string str;
		std::function<void()> onPressed;        // A function that determines what the Button will do when pressed.
		std::function<void()> onSelected;		// A function that determines what the Button will do when it is selected.
		std::function<void()> onUnselected; 	// A function that determines what the Button will do when it is unselected.
	};
}

#endif