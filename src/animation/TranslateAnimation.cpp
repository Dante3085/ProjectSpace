
#include "animation/TranslateAnimation.h"

#include <math.h>

#include "animation/Easing.h"
#include "utility/Util.h"
#include "utility/Log.h"

#include <SFML/Window/Mouse.hpp>

namespace ProjectSpace
{
	TranslateAnimation::TranslateAnimation(Translatable& translatable, sf::Vector2f const& from, sf::Vector2f const& to, float duration)
		: translatable{ translatable }, from{ from }, to{ to }, duration{ duration }, elapsedTime{0}, doUpdate{ false },
		currentVelocity{ -1, -1 }, easingFunction{ Easing::elastic_easeOut }, onFinished{ []() {} }, log{ &Log::getInstance() }
	{
		translatable.setPosition(from);
	}

	TranslateAnimation::TranslateAnimation()
		: translatable{nullptr}, from{0, 0}, to{50, 0}, duration{1000}, elapsedTime{0}, doUpdate{false},
		currentVelocity{-1, -1}, easingFunction{Easing::elastic_easeOut}, log{&Log::getInstance()}
	{

	}

	void TranslateAnimation::update(sf::Time time)
	{
		if (!doUpdate)
			return;

		if (translatable == nullptr)
		{
			log->defaultLog("@TranslateAnimation::update(): Translatable is nullptr. Returning and blocking update...", ll::ERR);
			doUpdate = false;
			return;
		}

		currentVelocity.x = easingFunction(elapsedTime, from.x, to.x - from.x, duration);
		currentVelocity.y = easingFunction(elapsedTime, from.y, to.y - from.y, duration);

		translatable->setPosition(currentVelocity);

		elapsedTime += time.asMilliseconds();

		// TranslateAnimation finished
		if (elapsedTime > duration)
		{
			elapsedTime = 0;
			doUpdate = false;
			translatable.setPosition(to);
			onFinished();

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

	void TranslateAnimation::setTranslatable(Translatable& translatable)
	{
		this->translatable = &translatable;
	}

	Translatable& TranslateAnimation::getTranslatable() const
	{
		return *translatable;
	}

	void TranslateAnimation::setOnFinished(std::function<void()> onFinished)
	{
		this->onFinished = onFinished;
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
