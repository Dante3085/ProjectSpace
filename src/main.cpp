
#include "Game.h"
#include "Tilemap.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
	using namespace ProjectSpace;

    /*Game g{ "ProjectSpace", WindowStyle::DEFAULT };
    g.start();*/

	TileMap t{ "rsrc/sfml-tileset.png" };
	t.registerTileImage("grass", sf::Vector2f{ 0, 0 }, sf::Vector2f{ 32, 0 },
		sf::Vector2f{ 32, 32 }, sf::Vector2f{ 0, 32 });

	t.registerTileImage("water", sf::Vector2f{ 32, 0 }, sf::Vector2f{ 64, 0 },
		sf::Vector2f{ 64, 32 }, sf::Vector2f{ 32, 32 });

	t.addTile("water", sf::Vector2f{ 0, 0 });
	t.addTile("water", sf::Vector2f{ 32, 0 });
	t.addTile("grass", sf::Vector2f{ 32, 32 });
	t.addTile("water", sf::Vector2f{ 100, 323 });
	t.addTile("grass", sf::Vector2f{ 789, 500 });

	sf::RenderWindow window{ sf::VideoMode{1920, 1080}, "Vertex tests" };

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		window.clear();
		window.draw(t);
		window.display();
	}

    return 0;
}