
#include "scenes/DebugScene.h"

namespace ProjectSpace
{
	DebugScene::DebugScene(sf::RenderWindow& window)
		: Scene{ window }, btn{ window, "DebugScene" }, btnAnim{ btn }
	{
		btnAnim.setDuration(500);
		btnAnim.setEasingFunction(Easing::back_easeOut);

		addEntities({ &btn, &btnAnim });
		addDrawables({ &btn });

		inputHandler.storeKeyState(sf::Keyboard::Left, false);
		inputHandler.storeKeyState(sf::Keyboard::Right, false);
	}

	void DebugScene::update(sf::Time time)
	{
		if (!inputHandler.wasKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			btnAnim.setFrom(btnAnim.getTranslatable().getPosition());
			btnAnim.setTo(sf::Vector2f{ 100, 100 });
			// btnAnim.setDuration(500 - btnAnim.getElapsedTime());
			btnAnim.start();
		}
		else if (!inputHandler.wasKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			btnAnim.setFrom(btnAnim.getTranslatable().getPosition());
			btnAnim.setTo(sf::Vector2f{ 1000, 0 });
			// btnAnim.setDuration(500 - btnAnim.getElapsedTime());
			btnAnim.start();
		}

		inputHandler.storeKeyState(sf::Keyboard::Left, sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		inputHandler.storeKeyState(sf::Keyboard::Right, sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

		Scene::update(time);
	}
}