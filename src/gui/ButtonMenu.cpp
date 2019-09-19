
#include "gui/ButtonMenu.h"

#include "utility/Log.h"

namespace ProjectSpace
{
	int ButtonMenu::numInstances = 0;

	ButtonMenu::ButtonMenu()
		: selected{0}, 
		inputContext{"include/input/contexts/ButtonMenuContext.txt"}
	{
		buttons[selected]->select();

		if (!buffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg"))
		{
			Log::getInstance().defaultLog("Couldn't load cursorMove sound effect.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}
		cursorMove.setBuffer(buffer);

		inputContext.setPredicate([]()
			{
				return true;
			});
		std::string inputContextName = "ButtonMenu";
		inputContextName += std::to_string(numInstances++);
		InputManager::getInstance().registerInputContext(inputContextName, &inputContext);
	}

	ButtonMenu::ButtonMenu(std::vector<Button const*> buttons) 
		: buttons{ buttons }, selected{0}, inputContext{ "include/input/contexts/ButtonMenuContext.txt" }
	{
		buttons[selected]->select();

		if (!buffer.loadFromFile("rsrc/audio/sfx/ff7CursorMove.ogg"))
		{
			Log::getInstance().defaultLog("Couldn't load cursorMove sound effect.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}
		cursorMove.setBuffer(buffer);

		inputContext.setPredicate([]()
		{
			return true;
		});
		std::string inputContextName = "ButtonMenu";
		inputContextName += std::to_string(numInstances++);
		InputManager::getInstance().registerInputContext(inputContextName, &inputContext);
	}

	void ButtonMenu::update(sf::Time time)
	{
		/*if (!inputHandler->wasKeyPressed(keyForward))
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
		}*/

		if (inputContext.hasActionFired(Action::BUTTON_MENU_FORWARD))
		{
			cursorMove.play();
			forward();
		}
		else if(inputContext.hasActionFired(Action::BUTTON_MENU_BACKWARD))
		{
			cursorMove.play();
			backward();
		}
		else if (inputContext.hasActionFired(Action::BUTTON_MENU_PRESS))
		{
			buttons[selected]->press();
		}
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