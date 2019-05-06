
#ifndef BATTLE_MENU_H
#define BATTLE_MENU_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "MenuElement.h"
#include "Button.h"
#include "ButtonMenu.h"
#include "VBox.h"
#include "HBox.h"
#include "../game/InputHandler.h"

namespace ProjectSpace
{
	class BattleMenu : public MenuElement
	{
	public:
		BattleMenu(sf::Vector2f position, InputHandler* inputHandler, sf::Window const& window);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		float getWidth() const override;
		float getHeight() const override;
		sf::Vector2f getPosition() const override;
		void setPosition(float x, float y) override;
		void setPosition(sf::Vector2f v) override;
		void move(float x, float y) override;
		void move(sf::Vector2f v) override;

	private:
		Button atkBtn; // attack button
		Button magBtn; // magic button
		Button itmBtn; // item button
		Button defBtn; // defend button
		ButtonMenu btnMenu; // keyboard, controller access to all BattleMenu buttons.
		VBox btnBox;

		sf::Vector2f position;
		InputHandler* inputHandler;
	};
}

#endif