
#include "Character.h"
#include <math.h>
#include "Util.h"

namespace ProjectSpace
{
	Character::Character(AnimatedSprite& animSprite, int strength, int defense, int agility, int intelligence)
	: animSprite{animSprite}, strength{strength}, defense{defense}, agility{agility}, intelligence{intelligence},
	movementKeys{{NORTH, sf::Keyboard::W}, {EAST, sf::Keyboard::D}, {SOUTH, sf::Keyboard::S}, {WEST, sf::Keyboard::A}},
	velocity{0, 0}, acceleration{0, 0}, frictionConstant{0.0001f}, speed{2.f}
	{

	}

	void Character::update(sf::Time time)
	{
		if (sf::Keyboard::isKeyPressed(movementKeys[NORTH]))
		{
			// velocity.y -= speed;
			animSprite.move(0, -10);
			animSprite.setAnimation(EAnimation::UP);
		}

		else if (sf::Keyboard::isKeyPressed(movementKeys[EAST]))
		{
			// velocity.x += speed;
			animSprite.move(10, 0);
			animSprite.setAnimation(EAnimation::RIGHT);
		}

		else if (sf::Keyboard::isKeyPressed(movementKeys[SOUTH]))
		{
			// velocity.y += speed;
			animSprite.move(0, 10);
			animSprite.setAnimation(EAnimation::DOWN);
		}

		else if (sf::Keyboard::isKeyPressed(movementKeys[WEST]))
		{
			// velocity.x -= speed;
			animSprite.move(-10, 0);
			animSprite.setAnimation(EAnimation::LEFT);
		}
		else
		{
			animSprite.setAnimation(EAnimation::IDLE);
		}

		/*animSprite.move(velocity);
		velocity *= pow(frictionConstant, time.asSeconds());

		if (abs(velocity.x) < 0.1f)
		{
			velocity.x = 0;
		}
		if (abs(velocity.y) < 0.1f)
		{
			velocity.y = 0;
		}*/

		animSprite.update(time);
	}

	void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(animSprite);
	}

	void Character::setMovementKeys(std::map<EDirection, sf::Keyboard::Key>& movementKeys)
	{
		this->movementKeys = movementKeys;
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

	void Character::setMovementKeys(std::map<EDirection, sf::Keyboard::Key> movementKeys)
	{
		this->movementKeys = movementKeys;
	}
}