
#include "BattleMenu.h"

#include <iostream>
#include <vector>

namespace ProjectSpace
{
	BattleMenu::BattleMenu(sf::Vector2f position, InputHandler* inputHandler, sf::Window const& window)
	: position{position}, inputHandler{inputHandler}, atkBtn{window, "Attack"}, magBtn{window, "Magic"}, itmBtn{window, "Item"}, defBtn{window, "Defend"}, 
	btnMenu{{&atkBtn, &magBtn, &itmBtn, &defBtn}, &(*inputHandler), sf::Keyboard::K, sf::Keyboard::I, sf::Keyboard::L},
	btnBox{{&atkBtn, &magBtn, &itmBtn, &defBtn}, position, 0}
	{
		atkBtn.setSize(100, 50);
		atkBtn.setOnPressed([]()
		{
			std::cout << "Attack" << std::endl;
		});

		magBtn.setSize(100, 50);
		magBtn.setOnPressed([]()
		{
			std::cout << "Magic" << std::endl;
		});

		itmBtn.setSize(100, 50);
		itmBtn.setOnPressed([]()
		{
			std::cout << "Item" << std::endl;
		});

		defBtn.setSize(100, 50);
		defBtn.setOnPressed([]()
		{
			std::cout << "Defend" << std::endl;
		});
	}

	void BattleMenu::update(sf::Time time)
	{
		btnMenu.update(time);
		btnBox.update(time);
	}

	void BattleMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(btnBox);
	}

	float BattleMenu::getWidth() const
	{
		// todo
		return -1;
	}

	float BattleMenu::getHeight() const
	{
		// todo
		return -1;
	}

	sf::Vector2f BattleMenu::getPosition() const
	{
		return position;
	}

	void BattleMenu::setPosition(float x, float y)
	{

	}

	void BattleMenu::setPosition(sf::Vector2f v)
	{

	}

	void BattleMenu::move(float x, float y)
	{

	}
	void BattleMenu::move(sf::Vector2f v)
	{

	}
}