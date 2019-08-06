
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
	class Character : public Entity, public sf::Drawable, public Logable
	{
	public:

		enum EDirection
		{
			NORTH,
			EAST,
			SOUTH,
			WEST
		};

	public:
		Character(AnimatedSprite& animSprite, int strength = 0, int defense = 0, int agility = 0, int intelligence = 0);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setMovementKeys(std::map<EDirection, sf::Keyboard::Key>& movementKeys);

		int getStrength();
		void setStrength(int strength);
		int getDefense();
		void setDefense(int defense);
		int getAgility();
		void setAgility(int agility);
		int getIntelligence();
		void setIntelligence(int intelligence);

		void setMovementKeys(std::map<EDirection, sf::Keyboard::Key> movementKeys);

		std::string toString() const override
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

	private:
		AnimatedSprite& animSprite;
		std::map<EDirection, sf::Keyboard::Key> movementKeys;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		float frictionConstant;
		float speed;

		int strength;
		int defense;
		int agility;
		int intelligence;
	};
}

#endif