
#ifndef BATTLE_ORDER_H
#define BATTLE_ORDER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <vector>

#include "rpg/Character.h"
#include "animation/TranslateAnimation.h"
#include "utility/Util.h"
#include "MenuElement.h"
#include "Portrait.h"

namespace ProjectSpace
{
	class BattleOrder : public Entity, public sf::Drawable
	{
	public:
		BattleOrder(std::vector<Character*> characters, sf::Vector2f const& position = sf::Vector2f{ 0, 0 });

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void cycle();

	private:
		sf::Vector2f position;
		std::vector<Character*> characters;
		std::vector<TranslateAnimation*> tas;

		bool doUpdate;
	};
}

#endif