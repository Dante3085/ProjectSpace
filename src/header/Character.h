
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>

#include "Entity.h"
#include "AnimatedSprite.h"
#include "Logable.h"

namespace ProjectSpace
{
	class Character : public Logable
	{
	public:
		Character(AnimatedSprite& animSprite, int strength = 0, int defense = 0, int agility = 0, int intelligence = 0);


		int getStrength();
		void setStrength(int strength);
		int getDefense();
		void setDefense(int defense);
		int getAgility();
		void setAgility(int agility);
		int getIntelligence();
		void setIntelligence(int intelligence);

		std::string toString() const override;

	private:
		int strength;
		int defense;
		int agility;
		int intelligence;
	};
}

#endif