
#ifndef DEBUG_SCENE_H
#define DEBUG_SCENE_H

#include <SFML/Window/Window.hpp>

#include "gui/Button.h"
#include "animation/TranslateAnimation.h"
#include "input/InputHandler.h"
#include "Scene.h"

namespace ProjectSpace
{
	class DebugScene : public Scene
	{
	public:
		DebugScene(sf::RenderWindow& window);

		void update(sf::Time time) override;

	private:
		Button btn;
		TranslateAnimation btnAnim;
		InputHandler inputHandler;
	};
}

#endif