
#include "Camera.h"

namespace ProjectSpace
{
	Camera::Camera(AnimatedSprite const& player, sf::RenderWindow& window, sf::Vector2f const& size) 
	: player{player}, window{window}, view{player.getPosition(), size} 
	{
		// Zooms out
		view.zoom(8.f);
	}

	void Camera::update(sf::Time time)
	{
		//sf::FloatRect playerBounds{player.getGlobalBounds()};
		//// Plus, weil Kamera mittig bewegt werden muss, nicht die Spielfigur.
		//view.setCenter(sf::Vector2f{playerBounds.left + (playerBounds.width / 2.f), playerBounds.top + (playerBounds.height / 2.f)});
		//window.setView(view);
	}

	sf::View const& Camera::getView() const
	{
		return view;
	}
}