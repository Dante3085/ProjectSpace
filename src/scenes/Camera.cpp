
#include "scenes/Camera.h"

namespace ProjectSpace
{
	Camera::Camera(Translatable const& translatable, sf::RenderWindow& window, sf::Vector2f const& size) 
	: translatable{translatable}, window{window}, view{translatable.getPosition(), size} 
	{
		// Zooms out
		view.zoom(8.f);
	}

	void Camera::update(sf::Time time)
	{
		// Der Zentrumspunkt des Translatable
		sf::Vector2f translatableCenter{translatable.getX() + (translatable.getWidth() / 2.f), 
			                            translatable.getY() + (translatable.getHeight() / 2.f)};
		view.setCenter(translatableCenter);
		window.setView(view);
	}

	sf::View const& Camera::getView() const
	{
		return view;
	}
}