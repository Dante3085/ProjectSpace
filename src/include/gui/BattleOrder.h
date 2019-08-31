
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
		BattleOrder(std::vector<Character*> characters, sf::Vector2f const& position = sf::Vector2f{ 0, 0 })
			: position{position}, characters {characters}, doUpdate{false}
		{

			/*Portrait* p = new Portrait{};
			p->setPosition(position);
			tas.push_back(new TranslateAnimation{ p, position, position + sf::Vector2f{0, 100}, 1000 });
			for (int i = 1; i < characters.size(); ++i)
			{
				p = new Portrait{};
				p->setPosition(tas[i - 1]->getMenuElement()->getPosition() + sf::Vector2f{ 0, 100 });
				tas.push_back(new TranslateAnimation{ p, p->getPosition(), p->getPosition() + sf::Vector2f{0, 100}, 1000 });
			}*/
		}

		void cycle()
		{
			/*doUpdate = true;
			for (TranslateAnimation* ta : tas)
			{
				ta->start();
			}*/
		}

		void update(sf::Time time) override
		{
			/*if (doUpdate)
			{
				for (TranslateAnimation* ta : tas)
				{
					ta->update(time);
				}
			}*/
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			/*for (TranslateAnimation* ta : tas)
			{
				target.draw(*ta->getMenuElement());
			}*/
		}

	private:
		sf::Vector2f position;
		std::vector<Character*> characters;
		std::vector<TranslateAnimation*> tas;

		bool doUpdate;
	};
}

#endif