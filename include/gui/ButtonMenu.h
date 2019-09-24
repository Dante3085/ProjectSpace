
#ifndef BUTTON_MENU_H
#define BUTTON_MENU_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <vector>

#include "scenes/Entity.h"
#include "input/InputManager.h"
#include "Button.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for selecting through a set of Buttons.
	 */
	class ButtonMenu : public Entity
	{
	public:
		ButtonMenu();
		ButtonMenu(std::vector<Button const*> buttons);

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
		int selected;	// Index of currently selected Button in this ButtonMenu.

		InputContext inputContext;

		sf::SoundBuffer buffer;
		sf::Sound cursorMove;

		static int numInstances;
	};
}

#endif