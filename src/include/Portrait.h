
#ifndef PORTRAIT_H
#define PORTRAIT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <string>

#include "MenuElement.h"

namespace ProjectSpace
{
	class Portrait : public MenuElement
	{
	public:
		Portrait(sf::Vector2f size = sf::Vector2f{50, 50}, 
			sf::Vector2f position = sf::Vector2f{0, 0}, std::string texturePath = "NONE");

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		float getWidth() const override;
		float getHeight() const override;
		sf::Vector2f getPosition() const override;
		void setPosition(float x, float y) override;
		void setPosition(sf::Vector2f v) override;
		void move(float x, float y) override;
		void move(sf::Vector2f v) override;
		void setFillColor(sf::Color color);

	private:
		sf::RectangleShape shape;
		sf::Texture texture;
	};
}

#endif