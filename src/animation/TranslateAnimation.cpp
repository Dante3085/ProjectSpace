
#include "TranslateAnimation.h"
#include "Util.h"
#include <math.h>

namespace ProjectSpace
{
	TranslateAnimation::TranslateAnimation(MenuElement* menuElement, sf::Vector2f from, sf::Vector2f to)
	: menuElement{menuElement}, doUpdate{false}, from{from}, to{to}, distance{to - from}, finished{false},
	frictionConstant{0.5f}, velocity{(to - menuElement->getPosition()) * (1.f/ 20.f)}
	{
		
	}

	void TranslateAnimation::update(sf::Time time)
	{
		if (doUpdate)
		{
			float distance = vectorLength(to - menuElement->getPosition());
			std::cout << "distance: " << distance << "\n";

			if (distance < 1.f)
			{
				menuElement->setPosition(to);
				doUpdate = false;
				finished = true;
				velocity = (to - from) * (1.f / 20.f);

				return;
			}

			// Is supposed to gradually reduce the velocity.
			// velocity *= pow(frictionConstant, time.asSeconds());
			
			static sf::Vector2f minVelocity{10.f, 10.f};
			velocity *= 0.9f;
			if (abs(velocity.x) < minVelocity.x || abs(velocity.y) < minVelocity.y)
			{
				velocity = (to - menuElement->getPosition()) * (1.f / 20.f);
			}

			menuElement->move(velocity);
		}
	}

	void TranslateAnimation::start()
	{
		doUpdate = true;
		velocity = (to - menuElement->getPosition()) * (1.f / 20.f);
	}

	void TranslateAnimation::pause()
	{
		doUpdate = false;
	}

	void TranslateAnimation::reset()
	{
		// menuElement->setPosition(from);
		doUpdate = false;
		finished = false;
	}

	sf::Vector2f TranslateAnimation::getFrom() const
	{
		return from;
	}

	void TranslateAnimation::setFrom(sf::Vector2f from)
	{
		this->from = from;
		distance = to - from;
	}

	sf::Vector2f TranslateAnimation::getTo() const
	{
		return to;
	}

	void TranslateAnimation::setTo(sf::Vector2f to)
	{
		this->to = to;
		distance = to - from;
	}

	void TranslateAnimation::setMenuElement(MenuElement* menuElement)
	{
		this->menuElement = menuElement;
	}

	MenuElement* TranslateAnimation::getMenuElement() const
	{
		return menuElement;
	}

	bool TranslateAnimation::isFinished() const
	{
		return finished;
	}
}