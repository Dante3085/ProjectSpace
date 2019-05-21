
#include "Tilemap.h"
#include <iostream>
#include <fstream>

namespace ProjectSpace
{
	void Tilemap::load(std::string const& tileset, sf::Vector2u tileSize, std::string const& tilemap, unsigned int width, unsigned int height)
	{
		std::ifstream ifs(tilemap);
		std::string tiles((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

		// load the tileset texture
		if (!this->tileset.loadFromFile(tileset))
		{
			std::cout << "@Tilemap::load(): Failed to load Tileset." << std::endl;
			return;
		}

		// resize the vertex array to fit the level size
		vertices.setPrimitiveType(sf::Quads);
		vertices.resize(width * height * 4);
		
		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
		{
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				// int tileNumber = tiles[i + j * width];
				int tileNumber = tiles[1];

				// find its position in the tileset texture
				int tu = tileNumber % (this->tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (this->tileset.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex * quad = &vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}
		}
	}

	void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &tileset;

		// draw the vertex array
		target.draw(vertices, states);
	}
}