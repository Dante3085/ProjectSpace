
#ifndef BATTLE_ORDER_H
#define BATTLE_ORDER_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <queue>
#include <algorithm>
#include <iostream>

#include "../rpg/Character.h"
#include "../animation/TranslateAnimation.h"
#include "MenuElement.h"
#include "Portrait.h"

namespace ProjectSpace
{
	class BattleOrder : public MenuElement
	{
	public:
		BattleOrder(std::vector<Character*> characters, sf::Vector2f position = sf::Vector2f{0, 0}, 
			float spacing = 0, float cycleDuration = 0.5f);
		~BattleOrder();

		void update(sf::Time time) override;
		void cycle();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		float getWidth() const override;
		float getHeight() const override;
		sf::Vector2f getPosition() const override;
		void setPosition(float x, float y) override;
		void setPosition(sf::Vector2f v) override;
		void move(float x, float y) override;
		void move(sf::Vector2f v) override;

	private:
		sf::Vector2f position;
		std::queue<Character*> characters;
		std::vector<Portrait*> portraits;
		std::vector<TranslateAnimation*> anims;
		float spacing;

		float width;
		float height;
	};
}

#endif