
#include "ExpandMenu.h"

namespace ProjectSpace
{
	ExpandMenu::ExpandMenu(std::map<Button*, std::vector<Button*>> const& buttons, 
		sf::Vector2f const& position, InputHandler* inputHandler)
	: buttons{buttons}, position{position}
	{
		// VBox und ButtonMenu für die obersten Buttons
		vboxs.push_back(VBox{5});
		buttonMenus.push_back(ButtonMenu{inputHandler});

		// VBoxen, ButtonMenus und TranslateAnimations für die Unterbuttons der obersten Buttons.
		for (int i = 0; i < buttons.size(); ++i)
		{
			vboxs.push_back(VBox{5});
			vboxs[i + 1].hide();
			buttonMenus.push_back(ButtonMenu{inputHandler});
		}

		// Buttons korrekt in die VBoxen und ButtonMenus einfügen.
		int i = 0;
		for (auto const& pair : buttons)
		{
			vboxs[0].addMenuElement(pair.first);
			buttonMenus[0].addButton(pair.first);
			for (Button const* btn : pair.second)
			{
				vboxs[i + 1].addMenuElement((MenuElement*)btn);
				buttonMenus[i + 1].addButton(btn);
			}

			// Funktion der obersten Buttons festlegen.
			pair.first->setOnPressed([this, i]()
			{
				if (vboxs[i + 1].isHidden())
				{
					vboxs[i + 1].show();
					tBackwardAnims[i].pause();
					tForwardAnims[i].start();
				}
				else
				{
					vboxs[i + 1].hide();
					tForwardAnims[i].pause();
					tBackwardAnims[i].start();
				}
			});
			++i;
		}

		// Alles korrekt positionieren
		vboxs[0].setPosition(position);
		for (int i = 1; i < vboxs.size(); ++i)
		{
			vboxs[i].setPosition(position);
			tForwardAnims.push_back(TranslateAnimation{&vboxs[i], position, sf::Vector2f{position.x + vboxs[0].getWidth() + 5, position.y}});
			tBackwardAnims.push_back(TranslateAnimation{&vboxs[i], sf::Vector2f{position.x + vboxs[0].getWidth() + 5, position.y}, position});
		}
	}

	void ExpandMenu::update(sf::Time time) 
	{
		for (VBox& v : vboxs)
		{
			v.update(time);
		}

		for (ButtonMenu& b : buttonMenus)
		{
			b.update(time);
		}

		for (TranslateAnimation& t : tForwardAnims)
		{
			t.update(time);
		}

		for (TranslateAnimation& t : tBackwardAnims)
		{
			t.update(time);
		}
	}

	void ExpandMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{ 
		for (VBox const& v : vboxs)
		{
			target.draw(v);
		}
	}

	float ExpandMenu::getWidth() const 
	{
		return -1;
	}

	float ExpandMenu::getHeight() const 
	{
		return -1;
	}

	sf::Vector2f ExpandMenu::getPosition() const 
	{
		return position;
	}

	void ExpandMenu::setPosition(float x, float y) 
	{
		position.x = x;
		position.y = y;
	}

	void ExpandMenu::setPosition(sf::Vector2f v) 
	{
		position = v;
	}

	void ExpandMenu::move(float x, float y) 
	{
		position.x += x;
		position.y += y;
	}

	void ExpandMenu::move(sf::Vector2f v) 
	{
		position += v;
	}
}