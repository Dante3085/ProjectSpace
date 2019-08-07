
#include "InputHandler.h"
#include "Log.h"

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

	bool InputHandler::wasKeyPressed(sf::Keyboard::Key key)
	{
		if (keyStates.count(key) == 0)
		{
			Log::getInstance() << lo::PTC << ll::ERR << lo::TIMESTAMP << "Given key's state is not stored."
				<< lo::STACKTRACE << lo::END << lo::EXIT;
		}
		return keyStates[key];
	}
}