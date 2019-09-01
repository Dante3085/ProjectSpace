
#ifndef TURN_BASED_COMBAT_H
#define TURN_BASED_COMBAT_H

#include <queue>
#include <algorithm>
#include <iostream>
#include <string>

#include "rpg/Character.h"
#include "scenes/Entity.h"
#include "utility/Log.h"

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
		TurnBasedCombat(std::vector<Character*> const& party1, std::vector<Character*> const& party2);

		void update(sf::Time time) override;

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

#endif