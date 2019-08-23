#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Scene.h"
#include "Button.h"
#include "TranslateAnimation.h"
#include "InputHandler.h"

namespace ProjectSpace
{
	class DebugScene : public Scene
	{
	public:
		DebugScene(sf::RenderWindow& window)
			: Scene{window}, btn{ window, "DebugScene" }, btnAnim{ &btn }
		{
			btnAnim.setDuration(500);
			btnAnim.setEasing(Easing::BACK_EASE_OUT);

			addEntities({ &btn, &btnAnim });
			addDrawables({&btn});

			inputHandler.storeKeyState(sf::Keyboard::Left, false);
			inputHandler.storeKeyState(sf::Keyboard::Right, false);
		}

		void update(sf::Time time) override
		{
			if (!inputHandler.wasKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				btnAnim.setFrom(btnAnim.getMenuElement()->getPosition());
				btnAnim.setTo(sf::Vector2f{ 100, 100 });
				// btnAnim.setDuration(500 - btnAnim.getElapsedTime());
				btnAnim.start();
			}
			else if (!inputHandler.wasKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				btnAnim.setFrom(btnAnim.getMenuElement()->getPosition());
				btnAnim.setTo(sf::Vector2f{ 1000, 0 });
				// btnAnim.setDuration(500 - btnAnim.getElapsedTime());
				btnAnim.start();
			}

			inputHandler.storeKeyState(sf::Keyboard::Left, sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
			inputHandler.storeKeyState(sf::Keyboard::Right, sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

			Scene::update(time);
		}

	private:
		Button btn;
		TranslateAnimation btnAnim;
		InputHandler inputHandler;
	};
}