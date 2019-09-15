
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <functional>
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <set>

namespace ProjectSpace
{
	class InputManager;

	class InputContext
	{
	public:
		InputContext(std::function<bool()> predicate);
		InputContext();

		void setPredicate(std::function<bool()> predicate);
		bool isValid() const;

	private:
		bool valid;
		std::function<bool()> predicate;

		friend class InputManager;
	};

	sf::Keyboard::Key& operator++(sf::Keyboard::Key& key);

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

		std::map<std::string, InputContext*> inputContexts;
		std::set<std::string> blockedInputContexts;
	};
}

#endif
