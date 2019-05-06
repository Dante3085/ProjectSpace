
#include "ButtonMenu.h"
#include <stdexcept>

namespace ProjectSpace
{
	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler) 
	: buttons{buttons}, inputHandler{inputHandler}, selected{0}, keyForward{sf::Keyboard::Down}, 
	keyBackward{sf::Keyboard::Up}, keyPress{sf::Keyboard::Enter}, btnForward{0}, btnBackward{1}, btnPress{2}
	{
		buttons[selected]->select();
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);
	}

	// TODO: Ich weiß, dass ButtonMenu::ButtonMenu die keys/buttons schon setzt und ich diese hier erneut setze.
	// Ich bin aber zu faul mir etwas anderes auszudenken.
	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler, 
		sf::Keyboard::Key keyForward, sf::Keyboard::Key keyBackward, sf::Keyboard::Key keyPress)
	: buttons{buttons}, inputHandler{inputHandler}, selected{0}, keyForward{keyForward}, keyBackward{keyBackward}, keyPress{keyPress}
	{
		buttons[selected]->select();
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);
	}

	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler, 
		unsigned int btnForward, unsigned int btnBackward, unsigned int btnPress)
	: buttons{buttons}, inputHandler{inputHandler}, selected{0}, btnForward{btnForward}, btnBackward{btnBackward}, btnPress{btnPress}
	{
		buttons[selected]->select();
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);
	}

	void ButtonMenu::update(sf::Time time)
	{
		if (!inputHandler->isKeyPressed(keyForward))
		{
			if (sf::Keyboard::isKeyPressed(keyForward))
			{
				forward();
			}
		}

		if (!inputHandler->isKeyPressed(keyBackward))
		{
			if (sf::Keyboard::isKeyPressed(keyBackward))
			{
				backward();
			}
		}

		if (!sf::Keyboard::isKeyPressed(keyPress))
		{
			if (inputHandler->isKeyPressed(keyPress))
			{
				buttons[selected]->press();
			}
		}

		inputHandler->storeKeyState(keyForward, sf::Keyboard::isKeyPressed(keyForward));
		inputHandler->storeKeyState(keyBackward, sf::Keyboard::isKeyPressed(keyBackward));
		inputHandler->storeKeyState(keyPress, sf::Keyboard::isKeyPressed(keyPress));
		// TODO: Store ButtonState
	}

	void ButtonMenu::forward()
	{
		buttons[selected]->unselect();
		buttons[selected = (selected + 1) == buttons.size() ? 0 : selected + 1]->select();
	}

	void ButtonMenu::backward()
	{
		buttons[selected]->unselect();
		buttons[selected = (selected - 1) == -1 ? (buttons.size() - 1) : selected - 1]->select();
	}

	void ButtonMenu::select(int index)
	{
		if (index < 0 || index >= buttons.size())
		{
			throw std::out_of_range{"@ButtonMenu::select(): Invalid index."};
		}
		buttons[selected]->unselect();
		buttons[selected = index]->select();
	}
}