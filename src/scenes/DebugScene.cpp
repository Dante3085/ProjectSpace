
#include "scenes/DebugScene.h"

namespace ProjectSpace
{
	DebugScene::DebugScene(sf::RenderWindow& window)
		: Scene{ window }, 
		btn{ window, "DebugScene" }, 
		btnAnim{ btn }
	{
		btnAnim.setDuration(500);
		btnAnim.setEasingFunction(Easing::back_easeOut);

		addEntities({ &btn, &btnAnim });
		addDrawables({ &btn });
	}

	void DebugScene::update(sf::Time time)
	{
		

		Scene::update(time);
	}
}