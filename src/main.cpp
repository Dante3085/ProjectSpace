
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
		sf::Vector2f{ 64, 64 }, sf::Vector2f{ 32, 64 });

	for (int i = 0; i < 100; ++i)
	{
			t.addTile("water", sf::Vector2f(64 * i, 64 * i), sf::Vector2f(96 * i, 64 * i),
				sf::Vector2f(96 * i, 96 * i), sf::Vector2f(64 * i, 96 * i));
	}
	t.addTile("grass", sf::Vector2f{ 0, 0 }, sf::Vector2f{ 100, 200 }, sf::Vector2f{ 300, 200 }, sf::Vector2f{ 50, 50 });

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