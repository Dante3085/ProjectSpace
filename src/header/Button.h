
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
		
		/**
		 * @brief      Constructs a Button with default visuals.
		 *
		 * @param[in]  onPressed  A function that determines what the Button will do when clicked with the Left Mouse Button.
		 * @param      window  Game's window. Used for getting the Mouse Position.
		 * @param[in]  string  Text of the Button.
		 */
		Button(std::function<void()> onPressed, sf::Window const& window, std::string string = "NONE");

		/**
		 * @brief      Constructs a Button with default visuals and empty onPressed behaviour.
		 *
		 * @param      window  The window
		 * @param[in]  string  The string
		 */
		Button(sf::Window const& window, std::string string = "NONE");

		/**
		 * @brief      Update the Button each frame. Checks for Mouse Interaction.
		 *
		 * @param[in]  time  The time.
		 */
		void update(sf::Time time) override;

		/**
		 * @brief      For drawing a Button with an sf::RenderWindow aka the Game's window.
		 *
		 * @param      target  The target
		 * @param[in]  states  The states
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief      Sets what the Button will do when pressed.
		 *
		 * @param[in]  onPressed  On left mouse click
		 */
		void setOnPressed(std::function<void()> onPressed);

		/**
		 * @brief      Sets what the Button will do when it is selected.
		 *
		 * @param[in]  onSelected  on selected
		 */
		void setOnSelected(std::function<void()> onSelected);

		/**
		 * @brief      Sets what the Button will do when it is unselected.
		 *
		 * @param[in]  onUnselected  on unselected
		 */
		void setOnUnselected(std::function<void()> onUnselected);

		/**
		 * @brief      Sets the Button's FillColor.
		 *
		 * @param[in]  color  The color
		 */
		void setFillColor(sf::Color color);

		/**
		 * @brief      Sets the Buttons opacity.
		 *
		 * @param[in]  opacity  The opacity
		 */
		void setOpacity(int opacity);

		/**
		 * @brief      Sets the Button's position.
		 *
		 * @param[in]  x     parameter_description
		 * @param[in]  y     parameter_description
		 */
		void setPosition(float x, float y) override;

		/**
		 * @brief      Sets the Button's position.
		 *
		 * @param[in]  v     { parameter_description }
		 */
		void setPosition(sf::Vector2f v);

		/**
		 * @brief      Moves the Button relative to it's current Position by the given amount.
		 *
		 * @param[in]  x     Amount Button will be moved on the x-Axis relative to it's current Position.
		 * @param[in]  y     Amount Button will be moved on the y-Axis relative to it's current Position.
		 */
		void move(float x, float y) override;

		/**
		 * @brief      Moves the Button relative to it's current Position by the given amount.
		 *
		 * @param[in]  v     Amount Button will be moved on the x-y-Axis relative to it's current Position.
		 */
		void move(sf::Vector2f v);
		
		/**
		 * @brief      Sets the size of the Button.
		 *
		 * @param[in]  width   The width
		 * @param[in]  height  The height
		 */
		void setSize(float width, float height);

		void setSize(sf::Vector2f const& size);

		/**
		 * @brief      Gets the position of the Button.
		 *
		 * @return     The position.
		 */
		sf::Vector2f getPosition() const override;

		/**
		 * @brief      Gets the width of the Button.
		 *
		 * @return     The width.
		 */
		float getWidth() const override;

		/**
		 * @brief      Gets the height of the Button.
		 *
		 * @return     The height.
		 */
		float getHeight() const override;

		/**
		 * @brief      Executes Button's behaviour on being selected.
		 */
		void select() const;

		/**
		 * @brief      Executes Button's behaviour on being unselected.
		 */
		void unselect() const;

		/**
		 * @brief      Executes Button's behaviour on being pressed.
		 */
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