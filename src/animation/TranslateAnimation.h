
#ifndef TRANSLATE_ANIMATION
#define TRANSLATE_ANIMATION

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../game/Entity.h"
#include "../menu/Button.h"

namespace ProjectSpace
{
	class TranslateAnimation : public Entity
	{
	public:
		TranslateAnimation(MenuElement* menuElement, sf::Vector2f from, sf::Vector2f to, float duration);

		void update(sf::Time time) override;
		void start();
		void stop();
		void reset();
		sf::Vector2f getFrom() const;
		void setFrom(sf::Vector2f from);
		sf::Vector2f getTo() const;
		void setTo(sf::Vector2f to);
		void setMenuElement(MenuElement* menuElement);
		MenuElement* getMenuElement() const;
		bool isFinished() const;

	private:
		MenuElement* menuElement;
		sf::Vector2f from;
		sf::Vector2f to;
		sf::Vector2f intervall;
		sf::Vector2f distance;
		bool doUpdate;
		bool finished;
		float duration;
	};
}

#endif