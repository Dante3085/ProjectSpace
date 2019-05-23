
#ifndef LAYER_COLLIDABLE_H
#define LAYER_COLLIDABLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "CollisionBox.h"
// #include "CollisionSphere.h"
#include "CollisionShape.h"

namespace ProjectSpace
{
	class LayerCollidable : public Collidable, public sf::Drawable
	{
	public:
		LayerCollidable(sf::Vector2f position = sf::Vector2f{ 0, 0 }, sf::Vector2f size = sf::Vector2f{ 50, 50 },
			std::vector<sf::Vector2f> points = {});

		bool collidesWith(Collidable const* partner) const override;
		sf::FloatRect getGlobalBounds() const override;
		sf::Shape const& getShape() const override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		CollisionBox cb;
		CollisionShape cs;
	};
}

#endif