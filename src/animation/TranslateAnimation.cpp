
#include "TranslateAnimation.h"
#include "Util.h"
#include <math.h>
#include "Log.h"
#include "Easing.h"

#include <SFML/Window/Mouse.hpp>

namespace ProjectSpace
{
	TranslateAnimation::TranslateAnimation(MenuElement* menuElement, sf::Vector2f const& from, sf::Vector2f const& to, float duration)
		: menuElement{ menuElement }, from{ from }, to{ to }, duration{ duration }, elapsedTime{0}, doUpdate{ false }, finished{ false },
		currentVelocity{ -1, -1 }, easingFunction{elastic_easeOut}, log{ &Log::getInstance() }
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
		*log << "{" << currentVelocity.x << ", " << currentVelocity.y << "}\n";

		menuElement->setPosition(currentVelocity);

		elapsedTime += time.asMilliseconds();

		if (elapsedTime > duration)
		{
			elapsedTime = 0;
			doUpdate = false;
			finished = true;
			return;
		}
	}

	void TranslateAnimation::setEasing(Easing easing)
	{
		switch(easing)
		{
			case Easing::BACK_EASE_IN:
			easingFunction = back_easeIn;
			break;
			case Easing::BACK_EASE_OUT:
			easingFunction = back_easeOut;
			break;
			case Easing::BACK_EASE_IN_OUT:
			easingFunction = back_easeInOut;
			break;

			case Easing::BOUNCE_EASE_IN:
			easingFunction = bounce_easeIn;
			break;
			case Easing::BOUNCE_EASE_OUT:
			easingFunction = bounce_easeOut;
			break;
			case Easing::BOUNCE_EASE_IN_OUT:
			easingFunction = bounce_easeInOut;
			break;

			case Easing::CIRC_EASE_IN:
			easingFunction = circ_easeIn;
			break;
			case Easing::CIRC_EASE_OUT:
			easingFunction = circ_easeOut;
			break;
			case Easing::CIRC_EASE_IN_OUT:
			easingFunction = circ_easeInOut;
			break;

			case Easing::CUBIC_EASE_IN:
			easingFunction = cubic_easeIn;
			break;
			case Easing::CUBIC_EASE_OUT:
			easingFunction = cubic_easeOut;
			break;
			case Easing::CUBIC_EASE_IN_OUT:
			easingFunction = cubic_easeInOut;
			break;

			case Easing::ELASTIC_EASE_IN:
			easingFunction = elastic_easeIn;
			break;
			case Easing::ELASTIC_EASE_OUT:
			easingFunction = elastic_easeOut;
			break;
			case Easing::ELASTIC_EASE_IN_OUT:
			easingFunction = elastic_easeInOut;
			break;

			case Easing::EXPO_EASE_IN:
			easingFunction = expo_easeIn;
			break;
			case Easing::EXPO_EASE_OUT:
			easingFunction = expo_easeOut;
			break;
			case Easing::EXPO_EASE_IN_OUT:
			easingFunction = expo_easeInOut;
			break;

			case Easing::LINEAR_EASE_NONE:
			easingFunction = linear_easeNone;
			break;
			case Easing::LINEAR_EASE_IN:
			easingFunction = linear_easeIn;
			break;
			case Easing::LINEAR_EASE_OUT:
			easingFunction = linear_easeOut;
			break;
			case Easing::LINEAR_EASE_IN_OUT:
			easingFunction = linear_easeInOut;
			break;

			case Easing::QUAD_EASE_IN:
			easingFunction = quad_easeIn;
			break;
			case Easing::QUAD_EASE_OUT:
			easingFunction = quad_easeOut;
			break;
			case Easing::QUAD_EASE_IN_OUT:
			easingFunction = quad_easeInOut;
			break;

			case Easing::QUINT_EASE_IN:
			easingFunction = quint_easeIn;
			break;
			case Easing::QUINT_EASE_OUT:
			easingFunction = quint_easeOut;
			break;
			case Easing::QUINT_EASE_IN_OUT:
			easingFunction = quint_easeInOut;
			break;

			case Easing::SINE_EASE_IN:
			easingFunction = sine_easeIn;
			break;
			case Easing::SINE_EASE_OUT:
			easingFunction = sine_easeOut;
			break;
			case Easing::SINE_EASE_IN_OUT:
			easingFunction = sine_easeInOut;
			break;
		}
	}

	void TranslateAnimation::start()
	{
		doUpdate = true;
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