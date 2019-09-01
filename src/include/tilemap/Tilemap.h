
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <unordered_map>
#include <vector>

namespace ProjectSpace
{
	class Tilemap : public sf::Drawable, public sf::Transformable
	{
	public:
		Tilemap(std::string const& tilesetPath);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setTileset(std::string const& tilesetPath);

		/*
		name: Refers to the region/image of the tileset that is defined by the following 4 texture coordiantes(1 Quad).
		upperLeft:  UpperLeft corner of Quad that defines the image being taken from the tileset.
		upperRight: UpperRight corner of Quad.
		lowerRight: LowerRight corner of Quad.
		lowerLeft:  LowerLeft corner of Quad.
		*/
		void registerTileImage(std::string const& name, sf::Vector2f upperLeft, sf::Vector2f upperRight,
			sf::Vector2f lowerRight, sf::Vector2f lowerLeft);

		/*
		tileImage: Refers to a tileImage previously registered with registerTileImage().
		upperLeft:  UpperLeft corner of Quad that defines the region of the window/RenderTarget that will be covered by the given tileImage.
		upperRight: UpperRight corner.
		lowerRight: LowerRight corner.
		lowerLeft:  LowerLeft corner.
		*/
		void addTile(std::string const& tileImage, sf::Vector2f upperLeft, sf::Vector2f upperRight,
			sf::Vector2f lowerRight, sf::Vector2f lowerLeft);

		/*
		tileImage: Refers to a tileImage previously registered with registerTileImage().
		upperLeft: UpperLeft corner of Quad that defines the region of the window/RenderTarget that will be covered by the given tileImage.
		Other 3 corners are taken from the texture coordinates of the tileImage. That means the tileImage will be displayed at upperLeft
		without any scaling.
		*/
		void addTile(std::string const& tileImage, sf::Vector2f upperLeft);

		void addTiles(int num, std::string const& tileImage, sf::Vector2f upperLeft, sf::Vector2f upperRight,
			sf::Vector2f lowerRight, sf::Vector2f lowerLeft);

		void addTiles(int num, std::string const& tileImage, sf::Vector2f upperLeft);

		/*
		Registers tileImages and adds tiles from information given by file. Format...
		TILE-IMAGE{name, (x1, y1), (x2, y2), (x3, y3), (x4, y4)} for registering a tileImage.
		TILE{name, (x1, y1), (x2, y2), (x3, y3), (x4, y4)} or
		TILE{name, (x1, y1)} for adding a tile.
		TILES{name, numberOfTiles, (x1, y1), (x2, y2), (x3, y3), (x4, y4)} or
		TILES{name, numberOfTiles, (x1, y1)} to add multiple tiles at once.
		*/
		void loadFromFile(std::string const& filename);

	private:

		sf::VertexArray vertices;
		sf::Texture tileset;
		std::unordered_map<std::string, std::vector<sf::Vector2f>> tileImages;
	};
}

#endif