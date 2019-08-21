#pragma once

#include <queue>
#include <algorithm>
#include <iostream>
#include <string>

#include "Character.h"
#include "Entity.h"
#include "Log.h"

namespace ProjectSpace
{
	enum class CombatAction 
	{
		INVALID = -1,
		ATTACK,
		MAGIC,
		ITEM,
		DEFEND
	};

	class TurnBasedCombat : public Entity
	{
	public:
		TurnBasedCombat(std::vector<Character*> const& party1, std::vector<Character*> const& party2)
			: party1{party1}, party2{party2}, nextAction{CombatAction::INVALID}, nextActionTarget{nullptr}
		{
			// Sort all Characters decending in terms of their agility stat.
			std::vector<Character*> temp{ party1 };
			temp.insert(temp.end(), party2.begin(), party2.end());

			std::sort(temp.begin(), temp.end(), [](Character* c1, Character* c2) -> bool
			{
					return c1->getAgility() >= c2->getAgility();
			});

			// Character with highest agility stat gets first turn.
			for (Character* c : temp)
			{
				queue.push(c);
			}
		}

		void update(sf::Time time) override
		{
			/*combatMenu.update(time);
			if (nextAction != Action::INVALID)
			{
				
			}*/
		}

	private:
		std::queue<Character*> queue;
		std::vector<Character*> party1;
		std::vector<Character*> party2;

		// TurnBasedCombatMenu combatMenu;
		CombatAction nextAction;
		Character* nextActionTarget;
		
	private:
	};
}