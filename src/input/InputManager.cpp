
#include "input/InputManager.h"

#include <algorithm>
#include <fstream>

#include "utility/Log.h"
#include "utility/FileIO.h"

namespace ProjectSpace
{
	std::map<std::string, sf::Keyboard::Key> InputContext::stringToKey
	{
		{"key::A", sf::Keyboard::A},
		{"key::B", sf::Keyboard::B},
		{"key::C", sf::Keyboard::C},
		{"key::D", sf::Keyboard::D},
		{"key::E", sf::Keyboard::E},
		{"key::F", sf::Keyboard::F},
		{"key::G", sf::Keyboard::G},
		{"key::H", sf::Keyboard::H},
		{"key::I", sf::Keyboard::I},
		{"key::J", sf::Keyboard::J},
		{"key::K", sf::Keyboard::K},
		{"key::L", sf::Keyboard::L},
		{"key::M", sf::Keyboard::M},
		{"key::N", sf::Keyboard::N},
		{"key::O", sf::Keyboard::O},
		{"key::P", sf::Keyboard::P},
		{"key::Q", sf::Keyboard::Q},
		{"key::R", sf::Keyboard::R},
		{"key::S", sf::Keyboard::S},
		{"key::T", sf::Keyboard::T},
		{"key::U", sf::Keyboard::U},
		{"key::V", sf::Keyboard::V},
		{"key::W", sf::Keyboard::W},
		{"key::X", sf::Keyboard::X},
		{"key::Y", sf::Keyboard::Y},
		{"key::Z", sf::Keyboard::Z},

		{"key::Num0", sf::Keyboard::Num0},
		{"key::Num1", sf::Keyboard::Num1},
		{"key::Num2", sf::Keyboard::Num2},
		{"key::Num3", sf::Keyboard::Num3},
		{"key::Num4", sf::Keyboard::Num4},
		{"key::Num5", sf::Keyboard::Num5},
		{"key::Num6", sf::Keyboard::Num6},
		{"key::Num7", sf::Keyboard::Num7},
		{"key::Num8", sf::Keyboard::Num8},
		{"key::Num9", sf::Keyboard::Num9},

		{"key::Escape", sf::Keyboard::Escape},
		{"key::LControl", sf::Keyboard::LControl},
		{"key::LShift", sf::Keyboard::LShift},
		{"key::LAlt", sf::Keyboard::LAlt},
		{"key::LSystem", sf::Keyboard::LSystem},
		{"key::RControl", sf::Keyboard::RControl},
		{"key::RShift", sf::Keyboard::RShift},
		{"key::RAlt", sf::Keyboard::RAlt},
		{"key::RSystem", sf::Keyboard::RSystem},
		{"key::Menu", sf::Keyboard::Menu},
		{"key::LBracket", sf::Keyboard::LBracket},
		{"key::RBracket", sf::Keyboard::RBracket},
		{"key::Semicolon", sf::Keyboard::Semicolon},
		{"key::Comma", sf::Keyboard::Comma},
		{"key::Period", sf::Keyboard::Period},
		{"key::Quote", sf::Keyboard::Quote},
		{"key::Slash", sf::Keyboard::Slash},
		{"key::Backslash", sf::Keyboard::Backslash},
		{"key::Tilde", sf::Keyboard::Tilde},
		{"key::Equal", sf::Keyboard::Equal},
		{"key::Hyphen", sf::Keyboard::Hyphen},
		{"key::Space", sf::Keyboard::Space},
		{"key::Enter", sf::Keyboard::Enter},
		{"key::Backspace", sf::Keyboard::Backspace},
		{"key::Tab", sf::Keyboard::Tab},
		{"key::PageUp", sf::Keyboard::PageUp},
		{"key::PageDown", sf::Keyboard::PageDown},
		{"key::End", sf::Keyboard::End},
		{"key::Home", sf::Keyboard::Home},
		{"key::Insert", sf::Keyboard::Insert},
		{"key::Delete", sf::Keyboard::Delete},
		{"key::Add", sf::Keyboard::Add},
		{"key::Subtract", sf::Keyboard::Subtract},
		{"key::Multiply", sf::Keyboard::Multiply},
		{"key::Divide", sf::Keyboard::Divide},
		{"key::Left", sf::Keyboard::Left},
		{"key::Right", sf::Keyboard::Right},
		{"key::Up", sf::Keyboard::Up},
		{"key::Down", sf::Keyboard::Down},

		{"key::Numpad0", sf::Keyboard::Numpad0},
		{"key::Numpad1", sf::Keyboard::Numpad1},
		{"key::Numpad2", sf::Keyboard::Numpad2},
		{"key::Numpad3", sf::Keyboard::Numpad3},
		{"key::Numpad4", sf::Keyboard::Numpad4},
		{"key::Numpad5", sf::Keyboard::Numpad5},
		{"key::Numpad6", sf::Keyboard::Numpad6},
		{"key::Numpad7", sf::Keyboard::Numpad7},
		{"key::Numpad8", sf::Keyboard::Numpad8},
		{"key::Numpad9", sf::Keyboard::Numpad9},

		{"key::F1", sf::Keyboard::F1},
		{"key::F2", sf::Keyboard::F2},
		{"key::F3", sf::Keyboard::F3},
		{"key::F4", sf::Keyboard::F4},
		{"key::F5", sf::Keyboard::F5},
		{"key::F6", sf::Keyboard::F6},
		{"key::F7", sf::Keyboard::F7},
		{"key::F8", sf::Keyboard::F8},
		{"key::F9", sf::Keyboard::F9},
		{"key::F10", sf::Keyboard::F10},
		{"key::F11", sf::Keyboard::F11},
		{"key::F12", sf::Keyboard::F12},
		{"key::F13", sf::Keyboard::F13},
		{"key::F14", sf::Keyboard::F14},
		{"key::F15", sf::Keyboard::F15},
	};

	std::map<std::string, Action> InputContext::stringToAction
	{
		{"list_up", Action::LIST_UP},
	    {"list_down", Action::LIST_DOWN},
		{"list_select", Action::LIST_SELECT},
		{"print", Action::PRINT},
	};
	std::map<std::string, State> InputContext::stringToState;

	InputContext::InputContext(std::string const& contextFile, std::function<bool()> predicate)
	: inputManager{&InputManager::getInstance()}, valid{false}, predicate{predicate}
	{
		parseContextFile(contextFile);
	}

	InputContext::InputContext(std::string const& contextFile)
		: inputManager{ &InputManager::getInstance() }, valid{ false }, predicate{ []() { return false; } }
	{
		parseContextFile(contextFile);
	}

	void InputContext::update()
	{
		for (auto& pair : keyToAction)
		{
			if (pair.second.second == "onPressed")
			{
				if (inputManager->onKeyPressed(pair.first))
				{
					actionsFired[pair.second.first] = true;
				}
				else
				{
					actionsFired[pair.second.first] = false;
				}
			}
			else if (pair.second.second == "onReleased")
			{
				if (inputManager->onKeyReleased(pair.first))
				{
					actionsFired[pair.second.first] = true;
				}
				else
				{
					actionsFired[pair.second.first] = false;
				}
			}
		}
	}

	void InputContext::setPredicate(std::function<bool()> predicate)
	{
		this->predicate = predicate;
	}

	bool InputContext::isValid() const
	{
		return valid;
	}

	bool InputContext::hasActionFired(Action action)
	{
		return actionsFired[action];
	}

	bool InputContext::isStateOn(State state)
	{
		// TODO: Dummy return value. Not yet implemented.
		return false;
	}

	void InputContext::parseContextFile(std::string const& contextFile)
	{
		std::string contextFile_commentsRemoved = removeCommentsAndEmtpyLines(contextFile);

		// TODO: Parse ContextFile
		std::ifstream inFile{ contextFile_commentsRemoved };

		std::string str;
		while (inFile >> str)
		{
			if (str.find("numKeyToActionMappings") != std::string::npos)
			{
				// 23 must be the index of the first digit of the number, since the string is fixed except for the number.
				// str.size() - 23 is therefore the index of the last digit.
				int numKeyToActionMappings = std::stoi(str.substr(23, str.size() - 23));

				for (int i = 0; i < numKeyToActionMappings; ++i)
				{
					// Get key.
					inFile >> str;
					// Check if given std::string for Key exists.
					if (stringToKey.count(str) == 0)
					{
						std::string msg = "Given std::string '";
						msg += str;
						msg += "' can not be translated into a sf::Keyboard::Key.";
						Log::getInstance().defaultLog(msg, ll::ERR, true);
					}
					sf::Keyboard::Key key = stringToKey[str];

					// Get Action input modus.
					inFile >> str;
					// Check if given Action input modus exists.
					if (str != "onPressed" && str != "onReleased")
					{
						Log::getInstance().defaultLog("onPressed and onReleased are currently the only modi for Action input.", ll::ERR, true);
					}
					std::string mode = str; // onPressed oder onReleased. TODO: Auch das irgendwie in map niederlegen. Nicht einfach if testen.

					// Get Action.
					inFile >> str;
					if (stringToAction.count(str) == 0)
					{
						std::string msg = "Given std::string '";
						msg += str;
						msg += "' can not be translated into an Action.";
						Log::getInstance().defaultLog(msg, ll::ERR, true);
					}
					Action action = stringToAction[str];

					keyToAction[key] = std::pair<Action, std::string>{action, mode};
					actionsFired[action] = false;
				}
			}
		}
	}

	std::string InputContext::removeCommentsAndEmtpyLines(std::string const& contextFile)
	{
		std::ifstream inFile{ contextFile };

		std::string contextFile_commentsRemoved = contextFile;
		contextFile_commentsRemoved.erase(contextFile_commentsRemoved.size() - 4);
		contextFile_commentsRemoved.append("_commentsRemoved.txt");
		std::ofstream outFile{ contextFile_commentsRemoved };

		char charBeforeComment = '-1';
		char c;
		while (inFile.get(c))
		{
			// Could be single line comment
			if (c == '/')
			{
				inFile.get(c);

				// that's a single line comment for shure.
				if (c == '/')
				{
					while (!inFile.eof())
					{
						inFile.get(c);

						// TODO: Checking for \r carraige return could fix upcoming problems.
						if (c == '\n')
						{
							if (charBeforeComment != '\n')
							{
								outFile << '\n';
							}
							break;
						}
					}
				}
				// Write '/' if there was no single line comment.
				// This has to be done because the previous get() ate the '/'.
				else
				{
					charBeforeComment = '/';
					outFile << '/';
				}
			}

			// Write normal file contents.
			else
			{
				charBeforeComment = c;
				outFile << c;
			}
		}

		return contextFile_commentsRemoved;
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

			// Let InputContext's Predicate function decide if the InputContext is valid
			// and update the InputContext.
			else
			{
				pair.second->valid = pair.second->predicate();
				pair.second->update();
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