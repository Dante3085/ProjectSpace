
#include "TranslateAnimation.h"
#include "Util.h"
#include <math.h>
#include "Log.h"
#include "Easing.h"

#include <SFML/Window/Mouse.hpp>

namespace ProjectSpace
{
	TranslateAnimation::TranslateAnimation(MenuElement* menuElement, sf::Vector2f const& from, sf::Vector2f const& to, float duration)
		: menuElement{ menuElement }, from{ from }, to{ to }, duration{ duration }, elapsedTime{0}, doUpdate{ false },
		currentVelocity{ -1, -1 }, easingFunction{ Easing::elastic_easeOut }, log{ &Log::getInstance() }
	{
		menuElement->setPosition(from);
	}

	void TranslateAnimation::update(sf::Time time)
	{
		// TODO: Mitten in einer anderen TranslateAnimation aufnehmen.

		if (!doUpdate)
			return;

		currentVelocity.x = easingFunction(elapsedTime, from.x, to.x - from.x, duration);
		currentVelocity.y = easingFunction(elapsedTime, from.y, to.y - from.y, duration);

		menuElement->setPosition(currentVelocity);

		elapsedTime += time.asMilliseconds();

		if (elapsedTime > duration)
		{
			elapsedTime = 0;
			doUpdate = false;
			return;
		}
	}

	void TranslateAnimation::setEasingFunction(Easing::EasingFunction easingFunction)
	{
		this->easingFunction = easingFunction;
	}

	void TranslateAnimation::start()
	{
		elapsedTime = 0;
		doUpdate = true;
	}

	void TranslateAnimation::pause()
	{
		doUpdate = false;
	}

	void TranslateAnimation::reset()
	{
		// TODO
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

	float TranslateAnimation::getDuration() const
	{
		return duration;
	}

	void TranslateAnimation::setDuration(float duration)
	{
		this->duration = duration;
	}

	float TranslateAnimation::getElapsedTime() const
	{
		return elapsedTime;
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