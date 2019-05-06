
#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Entity.h"
#include "../animation/AnimatedSprite.h"
#include "../Util.h"

namespace ProjectSpace
{
	class Camera : public Entity
	{
	public:
		Camera(AnimatedSprite const& player, sf::RenderWindow& window, sf::Vector2f const& size);

		void update(sf::Time time) override;
		sf::View const& getView() const;

	private:
		AnimatedSprite const& player;
		sf::RenderWindow& window;
		sf::View view;
	};
}

#endif 