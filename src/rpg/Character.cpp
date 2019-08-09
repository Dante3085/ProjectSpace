
#include "Character.h"
#include <math.h>
#include "Util.h"

namespace ProjectSpace
{
	Character::Character(AnimatedSprite& animSprite, int strength, int defense, int agility, int intelligence)
	: strength{strength}, defense{defense}, agility{agility}, intelligence{intelligence}
	{

	}

	int Character::getStrength()
	{
		return strength;
	}

	void Character::setStrength(int strength)
	{
		this->strength = strength;
	}

	int Character::getDefense()
	{
		return defense;
	}

	void Character::setDefense(int defense)
	{
		this->defense = defense;
	}

	int Character::getAgility()
	{
		return agility;
	}

	void Character::setAgility(int agility)
	{
		this->agility = agility;
	}

	int Character::getIntelligence()
	{
		return intelligence;
	}

	void Character::setIntelligence(int intelligence)
	{
		this->intelligence = intelligence;
	}

	std::string Character::toString() const 
	{
		std::string s = "Str: ";
		s.append(std::to_string(strength));
		s.append("Def: ");
		s.append(std::to_string(defense));
		s.append("Agi: ");
		s.append(std::to_string(agility));
		s.append("Int: ");
		s.append(std::to_string(intelligence));
		return s;
	}
}