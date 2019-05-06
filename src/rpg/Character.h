
#ifndef CHARACTER_H
#define CHARACTER_H

namespace ProjectSpace
{
	class Character
	{
	public:
		Character(int strength = 0, int defense = 0, int agility = 0, int intelligence = 0);

		int getStrength();
		void setStrength(int strength);
		int getDefense();
		void setDefense(int defense);
		int getAgility();
		void setAgility(int agility);
		int getIntelligence();
		void setIntelligence(int intelligence);

	private:
		int strength;
		int defense;
		int agility;
		int intelligence;
	};
}

#endif