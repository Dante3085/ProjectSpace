
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <map>
#include <string>
#include <vector>

namespace ProjectSpace
{
	class Tilemap : public sf::Drawable
	{
	public:
		Tilemap(sf::Vector2f position, sf::Vector2f tileSize, std::map<char, sf::Texture*> const& textures);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void loadFromFile(std::string const& filepath);

	private:
		sf::Vector2f position;
		sf::Vector2f tileSize;
		std::map<char, sf::Texture*> textures;
		std::vector<sf::RectangleShape> tiles;
	};
}

#endif