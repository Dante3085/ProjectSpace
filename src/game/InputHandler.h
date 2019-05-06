
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <map>
#include <functional>

#include "Entity.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for handling input.
	 * 			   (Bin mir nicht sicher, ob diese Implementierung vernuenftig ist
	 * 			    Im Endeffekt sind es ja nur Funktionen, die hier aufgerufen werden.)
	 */
	class InputHandler : public Entity
	{
	public:

		/**
		 * @brief      Adds the given input action to the InputHandler.
		 *
		 * @param[in]  action  The action
		 */
		void add(std::function<void()> action);

		/**
		 * @brief      Updates the InputHandler. Just calls every input action.
		 *
		 * @param[in]  time  The time
		 */
		void update(sf::Time time) override;

		
		/**
		 * @brief      Stores the pressed state of the given Key.
		 *
		 * @param[in]  key      The key.
		 * @param[in]  pressed  The pressed state.
		 */
		void storeKeyState(sf::Keyboard::Key key, bool pressed);

		/**
		 * @brief      Gets whether or not given Key was pressed the last time it's keyState was stored.
		 *
		 * @param[in]  key   The key
		 *
		 * @return     The key state.
		 */
		bool isKeyPressed(sf::Keyboard::Key key);

	private:
		std::vector<std::function<void()>> actions;   // All input actions of the InputHandler.
		std::map<sf::Keyboard::Key, bool> keyStates;
	};
}

#endif
