
#include "gui/ButtonMenu.h"

#include "utility/Log.h"

namespace ProjectSpace
{
	ButtonMenu::ButtonMenu(InputHandler* inputHandler)
	: buttons{}, inputHandler{inputHandler}, selected{0}, keyForward{sf::Keyboard::Down}, 
	keyBackward{sf::Keyboard::Up}, keyPress{sf::Keyboard::Enter}, btnForward{0}, btnBackward{1}, 
		btnPress{2}
	{
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);

		if (!buffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg"))
		{
			Log::getInstance().defaultLog("Couldn't load cursorMove sound effect.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}
		cursorMove.setBuffer(buffer);
	}

	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler) 
	: buttons{buttons}, inputHandler{inputHandler}, selected{0}, keyForward{sf::Keyboard::Down}, 
	keyBackward{sf::Keyboard::Up}, keyPress{sf::Keyboard::Enter}, btnForward{0}, btnBackward{1}, 
		btnPress{2}
	{
		buttons[selected]->select();
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);

		if (!buffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg"))
		{
			Log::getInstance().defaultLog("Couldn't load cursorMove sound effect.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}
		cursorMove.setBuffer(buffer);
	}

	// TODO: Ich weiß, dass ButtonMenu::ButtonMenu die keys/buttons schon setzt und ich diese hier erneut setze.
	// Ich bin aber zu faul mir etwas anderes auszudenken.
	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler, 
		sf::Keyboard::Key keyForward, sf::Keyboard::Key keyBackward, sf::Keyboard::Key keyPress)
	: buttons{buttons}, inputHandler{inputHandler}, selected{0}, keyForward{keyForward}, 
		keyBackward{keyBackward}, keyPress{keyPress}
	{
		buttons[selected]->select();
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);

		if (!buffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg"))
		{
			Log::getInstance().defaultLog("Couldn't load cursorMove sound effect.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}
		cursorMove.setBuffer(buffer);
	}

	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons, InputHandler* inputHandler, 
		unsigned int btnForward, unsigned int btnBackward, unsigned int btnPress)
	: buttons{buttons}, inputHandler{inputHandler}, selected{0}, btnForward{btnForward}, 
		btnBackward{btnBackward}, btnPress{btnPress}
	{
		buttons[selected]->select();
		inputHandler->storeKeyState(keyForward, false);
		inputHandler->storeKeyState(keyBackward, false);
		inputHandler->storeKeyState(keyPress, false);

		if (!buffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg"))
		{
			Log::getInstance().defaultLog("Couldn't load cursorMove sound effect.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}
		cursorMove.setBuffer(buffer);
	}

	void ButtonMenu::update(sf::Time time)
	{
		if (!inputHandler->wasKeyPressed(keyForward))
		{
			if (sf::Keyboard::isKeyPressed(keyForward))
			{
				// cursorMove.play();
				forward();
			}
		}

		if (!inputHandler->wasKeyPressed(keyBackward))
		{
			if (sf::Keyboard::isKeyPressed(keyBackward))
			{
				// cursorMove.play();
				backward();
			}
		}

		if (!sf::Keyboard::isKeyPressed(keyPress))
		{
			if (inputHandler->wasKeyPressed(keyPress))
			{
				// cursorMove.play();
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
			Log::getInstance() << lo::PTC << ll::ERR << "Invalid Index" << lo::STACKTRACE << lo::END;
			return;
		}

		buttons[selected]->unselect();
		buttons[selected = index]->select();
	}

	void ButtonMenu::addButton(Button const* button)
	{
		buttons.push_back(button);
	}
}