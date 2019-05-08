
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace ProjectSpace
{
	class Tilemap : public sf::Drawable, public sf::Transformable
	{
	public:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool load(std::string const& tileset, sf::Vector2u tileSize, int const* tiles, unsigned int width, unsigned int height);
		// loadFromFile(std::string const& tileset, std::string const& tilePattern, unsigned int width, unsigned int height)

	private:
		sf::VertexArray vertices;
		sf::Texture tileset;
	};
}

#endif