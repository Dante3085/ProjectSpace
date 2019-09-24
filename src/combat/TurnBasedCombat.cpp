
#include "combat/TurnBasedCombat.h"

namespace ProjectSpace
{
	TurnBasedCombat::TurnBasedCombat(std::vector<Character*> const& party1, std::vector<Character*> const& party2)
		: party1{ party1 }, 
		party2{ party2 }, 
		nextAction{ CombatAction::INVALID }, 
		nextActionTarget{ nullptr }
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

	void TurnBasedCombat::update(sf::Time time)
	{
		/*combatMenu.update(time);
		if (nextAction != Action::INVALID)
		{

		}*/
	}
}