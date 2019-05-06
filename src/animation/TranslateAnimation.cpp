
#include "TranslateAnimation.h"

namespace ProjectSpace
{
	TranslateAnimation::TranslateAnimation(MenuElement* menuElement, sf::Vector2f from, sf::Vector2f to, float duration)
	: menuElement{menuElement}, doUpdate{false}, from{from}, to{to}, duration{duration}, distance{to - from}, finished{false}
	{
	}

	void TranslateAnimation::update(sf::Time time)
	{
		if (doUpdate)
		{
			sf::Vector2f mPos = menuElement->getPosition();
			intervall = sf::Vector2f{distance.x / (duration * (1.0f / time.asSeconds())), distance.y / (duration * (1.0f / time.asSeconds()))};

				// BOTH POSITIVE
			if (intervall.x >= 0 && intervall.y >= 0)
			{
				if (mPos.x >= to.x && mPos.y >= to.y)
				{
					menuElement->setPosition(to);

					doUpdate = false;
					finished = true;
					return;
				}
			}

				// BOTH NEGATIVE
			else if (intervall.x < 0 && intervall.y < 0)
			{
				if (mPos.x <= to.x && mPos.y <= to.y)
				{
					menuElement->setPosition(to);

					doUpdate = false;
					finished = true;
					return;
				}
			}

				// X-POSITIV AND Y-NEGATIV
			else if (intervall.x >= 0 && intervall.y < 0)
			{
				if (mPos.x >= to.x && mPos.y <= to.y)
				{
					menuElement->setPosition(to);

					doUpdate = false;
					finished = true;
					return;
				}
			}

				// X-NEGATIVE AND Y-POSITIVE
			else
			{
				if (mPos.x <= to.x && mPos.y >= to.y)
				{
					menuElement->setPosition(to);

					doUpdate = false;
					finished = true;
					return;
				}
			}
			menuElement->move(intervall);
		}
	}

	void TranslateAnimation::start()
	{
		doUpdate = true;
	}

	void TranslateAnimation::stop()
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