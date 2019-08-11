#pragma once

#include "MenuElement.h"
#include <SFML/System/Vector2.hpp>
#include "Util.h"
#include "Entity.h"
#include "Log.h"

namespace ProjectSpace
{
	class TranslateAnimation2 : public Entity
	{
	public:
		TranslateAnimation2(MenuElement* m, sf::Vector2f const& from, sf::Vector2f const& to, int duration)
			: m{m}, from{from}, to{to}, duration{duration}, stepEachTick{vectorMultScalar(to-from, 1.0f/duration)}, running{false},
			elapsed{0}
		{
			m->setPosition(from);
		}

		void update(sf::Time deltaTime) override
		{
			if (running && m->getPosition() != to)
			{
				elapsed += deltaTime.asMilliseconds();
				m->move(stepEachTick);
			}
		}

		void start()
		{
			running = true;
		}

	private:
		MenuElement* m;
		sf::Vector2f from;
		sf::Vector2f to;
		int duration;
		sf::Vector2f stepEachTick;

		bool running;
		int elapsed;
		
	private:
		
	};
}