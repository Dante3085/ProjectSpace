
#include "InputHandler.h"
#include <stdexcept>

namespace ProjectSpace
{
	void InputHandler::add(std::function<void()> action)
	{
		actions.push_back(action);
	}

	void InputHandler::update(sf::Time time)
	{
		for (auto& a : actions)
		{
			a();
		}
	}

	void InputHandler::storeKeyState(sf::Keyboard::Key key, bool pressed)
	{
		keyStates[key] = pressed;
	}

	bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
	{
		if (keyStates.count(key) == 0)
		{
			throw std::invalid_argument{"@InputHandler::getKeyState(): Given key's state is not stored."};
		}
		return keyStates[key];
	}
}