
#ifndef BUTTON_MENU_H
#define BUTTON_MENU_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

#include "../game/Entity.h"
#include "../game/InputHandler.h"
#include "Button.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for selecting through a set of Buttons.
	 */
	class ButtonMenu : public Entity
	{
	public:
		ButtonMenu(InputHandler* inputHandler);
		ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler);
		ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler, 
			sf::Keyboard::Key keyForward, sf::Keyboard::Key keyBackward, sf::Keyboard::Key keyPress);
		ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler, 
			unsigned int btnForward, unsigned int btnBackward, unsigned int btnPress);

		void update(sf::Time time) override;

		/**
		 * @brief      Selects the next Button in this ButtonMenu.
		 */
		void forward();

		/**
		 * @brief      Selects the previous Button in this ButtonMenu.
		 */
		void backward();

		/**
		 * @brief      Selects the Button at index in this ButtonMenu.
		 * 			   Throws exception if index is invalid.
		 *
		 * @param[in]  index  The index of Button in this ButtonMenu.
		 */
		void select(int index);

		void addButton(Button const* button);

	private:
		std::vector<Button const*> buttons; // Buttons in this ButtonMenu.
		InputHandler* inputHandler; // InputHandler of this ButtonMenu's context to store key/button state information.
		int selected;	// Index of currently selected Button in this ButtonMenu.

		sf::Keyboard::Key keyForward;	// Key for selecting the next Button in this ButtonMenu.
		sf::Keyboard::Key keyBackward;	// Key for selecting the previous Button in this ButtonMenu.
		sf::Keyboard::Key keyPress;		// Key for pressing the currently selected Button in this ButtonMenu.
		unsigned int btnForward;		// ControllerButton for selecting the next Button in this ButtonMenu.
		unsigned int btnBackward;		// ControllerButton for selecting the previous Button in this ButtonMenu.
		unsigned int btnPress;			// ControllerButton for pressing the currently selected Button in this ButtonMenu.
	};
}

#endif