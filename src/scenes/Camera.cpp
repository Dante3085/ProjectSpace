
#include "scenes/Camera.h"

#include "utility/Util.h"

namespace ProjectSpace
{
	Camera::Camera(Translatable const& translatable, sf::RenderWindow& window, sf::Vector2f const& size) 
	: translatable{&translatable}, window{window}, view{translatable.getPosition(), size},
		offset{translatable.getWidth() / 2.f, translatable.getHeight() / 2.f}
	{
		// Zooms out
		view.zoom(8.f);
	}

	void Camera::update(sf::Time time)
	{
		sf::Vector2f translatableCenter{translatable->getX() + offset.x, translatable->getY() + offset.y};

		view.setCenter(translatableCenter);
		window.setView(view);
	}

	sf::View const& Camera::getView() const
	{
		return view;
	}

	Translatable const& Camera::getTranslatable() const
	{
		return *translatable;
	}

	void Camera::setTranslatable(Translatable const& translatable)
	{
		this->translatable = &translatable;
		offset.x = translatable.getWidth() / 2.f;
		offset.y = translatable.getHeight() / 2.f;
	}
}