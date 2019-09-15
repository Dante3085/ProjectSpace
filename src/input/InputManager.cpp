
#include "input/InputManager.h"

#include <algorithm>

#include "utility/Log.h"

namespace ProjectSpace
{
	InputContext::InputContext(std::function<bool()> predicate)
	: valid{false}, predicate{predicate}
	{}

	InputContext::InputContext()
		: valid{ false }, predicate{ []() { return false; } }
	{

	}

	void InputContext::setPredicate(std::function<bool()> predicate)
	{
		this->predicate = predicate;
	}

	bool InputContext::isValid() const
	{
		return valid;
	}

	sf::Keyboard::Key& operator++(sf::Keyboard::Key& key)
	{
		if (key == sf::Keyboard::KeyCount)
		{
			Log::getInstance().defaultLog("Out of range.", ll::ERR, true);
		}
		key = static_cast<sf::Keyboard::Key>(static_cast<int>(key) + 1);
		return key;
	}

	InputManager::InputManager()
	{
		using Key = sf::Keyboard::Key;

		for (Key k = Key::A; k < Key::KeyCount; ++k)
		{
			currentKeys[k] = false;
			previousKeys[k] = false;
		}

	}

	// Call at the top of GameLoop.
    void InputManager::updateCurrentKeys()
    {
    	for (auto& pair : currentKeys)
    	{
    		currentKeys[pair.first] = sf::Keyboard::isKeyPressed(pair.first);
    	}
    }

	// Call at the bottom of GameLoop.
    void InputManager::updatePreviousKeys()
    {
    	for (auto& pair : previousKeys)
    	{
    		previousKeys[pair.first] = currentKeys[pair.first];
    	}
    }

	// Call after updateCurrentKeys.
    void InputManager::updateInputContexts()
    {
    	for(auto& pair : inputContexts)
    	{
			// If current InputContext is blocked, make it invalid.
			if (blockedInputContexts.find(pair.first) != blockedInputContexts.end())
			{
				pair.second->valid = false;
			}

			// Let InputContext's Predicate function decide if the InputContext is valid.
			else
			{
				pair.second->valid = pair.second->predicate();
			}
    	}
    }

    void InputManager::registerInputContext(std::string const& name, InputContext* inputContext)
    {
		if (inputContexts.count(name) > 0)
		{
			std::string msg = "An InputContext with the given name '";
			msg += name;
			msg += "' is already known to the InputManager. Returning.";

			Log::getInstance().defaultLog(msg, ll::WARNING);
			return;
		}
    	inputContexts[name] = inputContext;
    }

	// Makes the given InputContext always invalid.
    void InputManager::blockInputContext(std::string const& name)
    {
		if (inputContexts.count(name) == 0)
		{
			std::string msg = "There is no InputContext with the given name '";
			msg += name;
			msg += "' in the InputManager. Returning.";

			Log::getInstance().defaultLog(msg, ll::WARNING);
			return;
		}
		blockedInputContexts.insert(name);
    }

	// Returns true if given key was previously not pressed and is now pressed, otherwise false.
    bool InputManager::onKeyPressed(sf::Keyboard::Key key) const
    {
    	return !previousKeys.at(key) && currentKeys.at(key);
    }

	// Returns true if given key was previously pressed and is now not pressed, otherwise false.
    bool InputManager::onKeyReleased(sf::Keyboard::Key key) const
    {
    	return previousKeys.at(key) && !currentKeys.at(key);
    }

	// Returns true if given key is now pressed, otherwise false.
    bool InputManager::isKeyPressed(sf::Keyboard::Key key) const
    {
    	return currentKeys.at(key);
    }

	// Returns true if given key is now pressed, otherwise false.
	bool InputManager::wasKeyPressed(sf::Keyboard::Key key) const
	{
		return previousKeys.at(key);
	}
}