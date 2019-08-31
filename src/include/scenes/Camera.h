
#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "animation/Translatable.h"
#include "Entity.h"

namespace ProjectSpace
{
	class Camera : public Entity
	{
	public:
		Camera(Translatable const& translatable, sf::RenderWindow& window, sf::Vector2f const& size);

		void update(sf::Time time) override;
		sf::View const& getView() const;

	private:
		Translatable const& translatable;
		sf::RenderWindow& window;
		sf::View view;
	};
}

#endif 