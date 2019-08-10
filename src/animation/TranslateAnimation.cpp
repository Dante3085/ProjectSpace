
#include "TranslateAnimation.h"
#include "Util.h"
#include <math.h>
#include "Log.h"

namespace ProjectSpace
{
	TranslateAnimation::TranslateAnimation(MenuElement* menuElement, sf::Vector2f const& from, sf::Vector2f const& to)
		: menuElement{ menuElement }, from{ from }, to{ to }, minDistance{ 0.1f }, doUpdate{ false }, finished{ false },
		  velocityModifier{ 1.0f / 20.0f }, currentVelocity{ (to - menuElement->getPosition()) * velocityModifier }, 
		  minVelocity{10, 0}, log{ &Log::getInstance() }
	{
	}

	void TranslateAnimation::update(sf::Time time)
	{
		if (doUpdate)
		{
			// Compute distance between current position of menuElement and goal position.
			float distance = vectorLength(to - menuElement->getPosition());

			/* If distance is smaller than a minimum,  just place menuElement at goal position
			   and stop the process.
			*/
			if (distance < minDistance)
			{
				menuElement->setPosition(to);
				doUpdate = false;
				finished = true;
				currentVelocity = (to - menuElement->getPosition()) * velocityModifier;

				return;
			}

			/* Move the menuElement relative to it's current position by the current velocity.
			*/
			menuElement->move(currentVelocity);

			// Decrease velocity with each tick.
			currentVelocity *= 0.8f;

			static sf::Vector2f minVelocity{ 10.f, 10.f };

			// If velocity is smaller than a minimum, reset it to it's initial value.
			if (abs(currentVelocity.x) < minVelocity.x || abs(currentVelocity.y) < minVelocity.y)
			{
				currentVelocity = (to - menuElement->getPosition()) * velocityModifier;
			}
		}
	}

	void TranslateAnimation::start()
	{
		doUpdate = true;
		currentVelocity = (to - menuElement->getPosition()) * velocityModifier;
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
	}

	sf::Vector2f TranslateAnimation::getTo() const
	{
		return to;
	}

	void TranslateAnimation::setTo(sf::Vector2f to)
	{
		this->to = to;
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

	bool TranslateAnimation::isUpdating() const
	{
		return doUpdate;
	}

	void TranslateAnimation::reverse()
	{
		sf::Vector2f temp{from};
		from = to;
		to = temp;
	}
}