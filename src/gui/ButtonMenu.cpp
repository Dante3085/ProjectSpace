
#include "gui/ButtonMenu.h"

#include "utility/Log.h"

namespace ProjectSpace
{
	int ButtonMenu::numInstances = 0;

	ButtonMenu::ButtonMenu()
		: buttons{},
		selected{0}, 
		inputContext{"include/input/contexts/ButtonMenuContext.txt"},
		buffer{},
		cursorMove{}
	{
		buttons[selected]->select();

		if (!buffer.loadFromFile("rsrc/audio/sfx/test.wav"))
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
		: buttons{ buttons }, 
		selected{0}, 
		inputContext{ "include/input/contexts/ButtonMenuContext.txt" },
		buffer{}, 
		cursorMove{}
	{
		buttons[selected]->select();

		if (!buffer.loadFromFile("rsrc/audio/sfx/test.wav"))
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