
#include "Tilemap.h"
#include <fstream>
#include <iostream>

namespace ProjectSpace
{
	Tilemap::Tilemap(sf::Vector2f position, sf::Vector2f tileSize, std::map<char, sf::Texture*> const& textures)
		: position{ position }, tileSize{ tileSize }, textures{ textures }
	{

	}

	void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		/*for (std::vector<sf::RectangleShape> const& row : tiles)
		{
			for (sf::RectangleShape const& shape : row)
			{
				target.draw(shape);
			}
		}*/

		for (sf::RectangleShape const& shape : tiles)
		{
			target.draw(shape); 
		}
	}
	
	void Tilemap::loadFromFile(std::string const& filepath)
	{
		std::ifstream ifs(filepath);
		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

		int row = 0;
		int col = 0;

		// std::cout << "tilemap_content: " << std::endl << content << std::endl;

		for (char const& c : content)
		{
			// Check for next row.
			if (c == '\n')
			{
				++row;
				col = 0;
			}

			// Check if read character represents a texture.
			else if (textures.count(c))
			{
				sf::RectangleShape shape{ tileSize };
				shape.setPosition(position.x + (col * tileSize.x), position.y + (row * tileSize.y));
				shape.setTexture(textures[c]);

				tiles.push_back(shape);

				++col;
			}

			else
			{
				++col;
			}
		}

	}
}