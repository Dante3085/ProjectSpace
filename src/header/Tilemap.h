
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

#include "Log.h"

namespace ProjectSpace
{
	class TileMap : public sf::Drawable, public sf::Transformable
	{
	public:
		TileMap(std::string const& tilesetPath)
		{
			tileset.loadFromFile(tilesetPath);
		}

		/*
		name: Refers to the region/image of the tileset that is defined by the following 4 texture coordiantes(1 Quad).
		upperLeft:  UpperLeft corner of Quad that defines the image being taken from the tileset.
		upperRight: UpperRight corner of Quad that defines the image being taken from the tileset.
		lowerRight: LowerRight corner of Quad that defines the image being taken from the tileset.
		lowerLeft:  LowerLeft corner of Quad that defines the image being taken from the tileset.
		*/
		void registerTileImage(std::string const& name, sf::Vector2f const& upperLeft, sf::Vector2f const& upperRight,
			                   sf::Vector2f const& lowerRight, sf::Vector2f const& lowerLeft)
		{
			std::vector<sf::Vector2f> textureCoordinates;
			textureCoordinates.push_back(upperLeft);
			textureCoordinates.push_back(upperRight);
			textureCoordinates.push_back(lowerRight);
			textureCoordinates.push_back(lowerLeft);

			tileImages[name] = textureCoordinates;

			vertices.setPrimitiveType(sf::PrimitiveType::Quads);
		}

		void addTile(std::string const& tileImage, sf::Vector2f const& upperLeft, sf::Vector2f const& upperRight,
			         sf::Vector2f const& lowerRight, sf::Vector2f const& lowerLeft)
		{
			if (tileImages.count(tileImage) == 0)
			{
				Log::getInstance() << lo::PTC << ll::ERR << lo::TIMESTAMP << "Given tileImage was not registered to this TileMap. Returning..."
					               << lo::STACKTRACE << lo::END;
				return;
			}

			std::vector<sf::Vector2f> tileImageCoords = tileImages[tileImage];

			sf::Vertex vertexUpperLeft{upperLeft, tileImageCoords[0]};
			sf::Vertex vertexUpperRight{upperRight, tileImageCoords[1]};
			sf::Vertex vertexLowerRight{ lowerRight, tileImageCoords[2] };
			sf::Vertex vertexLowerLeft{ lowerLeft, tileImageCoords[3] };

			vertices.append(vertexUpperLeft);
			vertices.append(vertexUpperRight);
			vertices.append(vertexLowerRight);
			vertices.append(vertexLowerLeft);
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			// apply the transform
			states.transform *= getTransform();

			// apply the tileset texture
			states.texture = &tileset;

			// draw the vertex array
			target.draw(vertices, states);
		}

	private:

		sf::VertexArray vertices;
		sf::Texture tileset;
		std::unordered_map<std::string, std::vector<sf::Vector2f>> tileImages;
	};
}

#endif