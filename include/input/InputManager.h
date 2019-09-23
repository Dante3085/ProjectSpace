
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>
#include <map>
#include <string>
#include <set>
#include <utility>
#include <iostream>

#include "input/InputConstants.h"

namespace ProjectSpace
{
	// Forward declarations
	class istream;
	class InputManager;
	class Log;

	// Usefull stuff.
	// For incrementing a Key variable in loops and other stuff.
	sf::Keyboard::Key& operator++(sf::Keyboard::Key& key);
	sf::Mouse::Button& operator++(sf::Mouse::Button& mouseButton);
	std::string toString(Action action);
	std::string toString(State state);
	std::string toString(sf::Mouse::Button button);
	std::string toString(sf::Keyboard::Key key);
	std::ostream& operator<<(std::ostream& stream, State state);

	class InputContext
	{
	public:
		InputContext(std::string const& contextFile, std::function<bool()> predicate);
		InputContext(std::string const& contextFile);

		void update();

		void setPredicate(std::function<bool()> predicate);
		bool isValid() const;

		bool hasActionFired(Action action);
		void fireAction(Action action);

		bool isStateOn(State state);
		bool onStateOn(State state);
		bool onStateOff(State state);

		// Helper for ContextFile parsing.
	private:
		void parseContextFile(std::string const& contextFile);
		std::string removeCommentsAndEmtpyLines(std::string const& contextFile);

		// Helper structs
	private:
		using KeyInputMode = bool(InputManager::*)(sf::Keyboard::Key) const;   // Function pointer to member functions of InputManager that check for key stuff.
		using MouseInputMode = bool(InputManager::*)(sf::Mouse::Button) const; // Function pointer to member functions of InputManager that check for Mouse stuff.
		using JoystickInputMode = bool(InputManager::*)(unsigned int joystickButton) const; // Function pointer to member functions of InputManager that check for Joystick stuff.

		// TODO: Die Unterscheidung auf KeyData, MouseData und JoystickData könnte vielleicht durch Union verhindert werden.
		// Bin mir aber nicht sicher, ob das hier Sinn macht.

		struct ActionKeyData
		{
			Action action;
			KeyInputMode keyInputMode;
		};

		struct ActionMouseData
		{
			Action action;
			MouseInputMode mouseInputMode;
		};

		struct ActionJoystickData
		{
			Action action;
			JoystickInputMode joystickInputMode;
		};

		struct StateKeyData
		{
			State state;
			KeyInputMode keyInputMode;
		};

		struct StateMouseData
		{
			State state;
			MouseInputMode mouseInputMode;
		};

		struct StateJoystickData
		{
			State state;
			JoystickInputMode joystickInputMode;
		};

	private:
		InputManager* inputManager;
		bool valid;
		std::function<bool()> predicate;

		std::map<sf::Keyboard::Key, ActionKeyData> keyToAction;  // Stores which Key fires an Action and in which way (onPressed/onReleased).
		// std::map<ControllerButton, std::tuple<Action, std::string>> controllerButtonToAction;

		std::map<sf::Keyboard::Key, StateKeyData> keyToStateOn;  // Stores which Key turns a State on and in which way (onPressed/onReleased).
		std::map<sf::Keyboard::Key, StateKeyData> keyToStateOff; // Stores which Key turns a State off and in which way (onPressed/onReleased).

		std::map<Action, bool> actionsFired;  // Stores if an Action has been fired or not.
		std::map<State, bool> currentStates;  // Stores if a State is on or not in the current udpate() iteration.
		std::map<State, bool> previousStates; // Stores if a State was on or not in the previous update() iteration.

		// InputManager needs to be able to block an InputContext by having access to it's private members.
		// TODO: Vielleicht krieg ich das aucht ohne friend intern in InputContext hin.
		friend class InputManager;
	};

	class InputManager
	{
	public:
		static InputManager& getInstance()
		{
			static InputManager singleton;
			return singleton;
		}

		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

		// Call inside Event-Loop.
		void updateCurrentInputStates(sf::Event event);

		// Call at the bottom of Game-Loop(last instruction).
		// Updates previousInputStates and other stuff that needs to be reset before going to the next 
		// Game-Loop iteration.
		void updateBeforeNextIteration();

		// Call after updateCurrentKeys outside of Event-Loop(first instruction after Event-Loop).
		void updateInputContexts();
		
		bool onKeyPressed(sf::Keyboard::Key key) const;
		bool onKeyReleased(sf::Keyboard::Key key) const;
		bool isKeyPressed(sf::Keyboard::Key key) const;
		bool wasKeyPressed(sf::Keyboard::Key key) const;

		bool onMouseButtonPressed(sf::Mouse::Button mouseButton) const;
		bool onMouseButtonReleased(sf::Mouse::Button mouseButton) const;
		bool isMouseButtonPressed(sf::Mouse::Button mouseButton) const;
		bool wasMouseButtonPressed(sf::Mouse::Button mouseButton) const;
		bool hasMouseMoved() const;
		sf::Vector2i getMousePosition() const;

		// 0 is not moved.
		float getMouseWheelDelta() const;

		void registerInputContext(std::string const& name, InputContext* inputContext);
		void blockInputContext(std::string const& name);

	private:
		InputManager();

		// sf::Keyboard
		std::map<sf::Keyboard::Key, bool> currentKeys;
		std::map<sf::Keyboard::Key, bool> previousKeys;
		sf::Keyboard::Key lastUpdatetKey;

		// sf::Mouse
		std::map<sf::Mouse::Button, bool> currentMouseButtons;
		std::map<sf::Mouse::Button, bool> previousMouseButtons;
		sf::Mouse::Button lastUpdatetMouseButton;
		bool mouseMovedThisFrame;
		sf::Vector2i currentMousePosition;
		float mouseWheelDelta;

		// TODO: std::map<std::string, std::pair<InputContext*, bool>> inputContexts.
		// The std::set is not necessary for checking blocked InputContexts.
		std::map<std::string, InputContext*> inputContexts;
		std::set<std::string> blockedInputContexts;
	};
}

#endif
