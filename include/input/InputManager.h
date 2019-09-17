
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <functional>
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <set>
#include <utility>

#include "input/InputConstants.h"

namespace ProjectSpace
{
	// Forward declarations
	class istream;
	class InputManager;
	class Log;

	// For incrementing a Key variable in loops and other stuff.
	sf::Keyboard::Key& operator++(sf::Keyboard::Key& key);

	class InputContext
	{
	public:
		InputContext(std::string const& contextFile, std::function<bool()> predicate);
		InputContext(std::string const& contextFile);

		void update();

		void setPredicate(std::function<bool()> predicate);
		bool isValid() const;

		bool hasActionFired(Action action);
		bool isStateOn(State state);

		// Helper for ContextFile parsing.
	private:
		void parseContextFile(std::string const& contextFile);
		std::string removeCommentsAndEmtpyLines(std::string const& contextFile);

	private:
		InputManager* inputManager;
		bool valid;
		std::function<bool()> predicate;

		using InputMode = bool(InputManager::*)(sf::Keyboard::Key) const; // Function pointer to member functions of InputManager that check for key stuff.

		std::map<sf::Keyboard::Key, std::pair<Action, InputMode>> keyToAction;  // Maps a Key to an Action and it's mode(onPressed/onReleased).
		// std::map<ControllerButton, std::tuple<Action, std::string>> controllerButtonToAction;

		std::map<sf::Keyboard::Key, std::pair<State, InputMode>> keyToStateOn;
		std::map<sf::Keyboard::Key, std::pair<State, InputMode>> keyToStateOff;

		std::map<Action, bool> actionsFired;  // Stores if an Action has been fired or not.
		std::map<State, bool> statesOn;       // Stores if a State is on or not.

		static std::map<std::string, sf::Keyboard::Key> stringToKey; // Lookup-Table to convert std::string from ContextFile to sf::Keyboard::Key.
		static std::map<std::string, Action> stringToAction;	     // Lookup-Table to convert std::string from ContextFile to Action.
		static std::map<std::string, State> stringToState;	         // Lookup-Table to convert std::string from ContextFile to State.

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

		void updateCurrentKeys();
		void updatePreviousKeys();
		void updateInputContexts();

		void registerInputContext(std::string const& name, InputContext* inputContext);
		void blockInputContext(std::string const& name);
		
		bool onKeyPressed(sf::Keyboard::Key key) const;
		bool onKeyReleased(sf::Keyboard::Key key) const;
		bool isKeyPressed(sf::Keyboard::Key key) const;
		bool wasKeyPressed(sf::Keyboard::Key key) const;

	private:
		InputManager();

		std::map<sf::Keyboard::Key, bool> currentKeys;
		std::map<sf::Keyboard::Key, bool> previousKeys;

		// TODO: std::map<std::string, std::pair<InputContext*, bool>> inputContexts.
		// The std::set is not necessary for checking blocked InputContexts.
		std::map<std::string, InputContext*> inputContexts;
		std::set<std::string> blockedInputContexts;
	};
}

#endif
