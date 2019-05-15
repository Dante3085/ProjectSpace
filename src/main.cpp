
/*#include "Game.h"
#include "Util.h"

using namespace ProjectSpace;*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

/* TODO

 - Während eine Animation abgespielt wird, tritt an immer derselben Stelle ein Ruckler auf.

 - Speicherverwaltung

 - RessourceHandler (Laden von Texturen Audio bzw. externen Ressourcen)

 - Event System

 - Audio

 - Save / Load

 - TextBox

 - Logger

 - Exception Handling

 - Kamera (SFML "Views")

 - (Vorschlag) Aufteilung der Quelldateien in Unterordner. Die Klassen "Animation" und "AnimatedSprite" in Ordner "Sprites".
   Die Klassen "Textbox", "Button", ... in den Ordner GUI. Darueber kann man sich im Team nochmal unterhalten.

 - Problem mit Button MouseEnter/MouseExit, wenn Fenster auf Monitor mit anderer Aufloesung verschoben wird.

 - In-Game-Console: Waehrend das Spiel laeuft Code eingeben und sachen veraendern.

 - Das gesamte Programm ruckelt in regelmaessigen Abstaenden.

 - Menue Buttons per Controller steuern können.

 - BattleOrder Anzeige (Vergleiche Final Fantasy 10)

 - Debugger

 - Collision Detection: Unterscheiden, mit was kollidiert wurde (Mauer => Charakter stoppen; Sumpf => Charakter verlangsamen; ...)

 - Polygon Collision Detection: Line Intersection

 - Line2D: intersects(Line2D) Funktion, anstatt mit operator==

 - Util::FloatRect operator<<

 - Separating Axis Theorem for Collision Detection

 - Problem: Pointer vs C++-Reference: Beides ist in diesem Projekt inkonsistent verwendent.

 - KnightSprite schlanker machen.

 - Seperating Axis Theorem.

 - Pufferbereich in Kollision, um Kollision nicht ständig auszulösen.

 - View Kamera

 - Menü, dass sich auf veränderndem View der Kamera immer an derselben Stelle öffnet und schließt.
   (Camera View abhängige Elemente, nicht Default View abhängig)

 - Schnelleres Kompilieren: Trennung auf h und cpp (Bedarfsgerechtes Kompilieren mit make)

 - automatic makefile.

 - InputHandler::isKeyPressed() Name macht den Eindruck als ob der wirklich aktuelle Drueckzustand eines Buttons abgerufen wird.
   Dabei ist es der letzte gespeicherte. Das ist etwas uneindeutig.

 - Window der Anwedung global verfügbar machen, damit nicht immer über Parameter übergeben werden muss.
   Andererseits signalisiert der Parameter die Absicht vernünftig

 - Camera beim Scene-Wechsel irgendwie resetten, da Kameraeinstellung von der Camera einer Scene in der naechsten Scene bestehen bleibt,
 die Camera aber nicht mehr geupdatet wird.

 - Tilemap mit VertexArray. Anzahl der sf::Drawable::draw calls bestimmt Performance. VertexArrays können in einem draw call gezeichnet werden.
   (https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php)

 - Game Instanz als Singleton

*/

/* USEFULL LINKS
 - SFML Dokumentation: https://www.sfml-dev.org/documentation/2.5.1/modules.php
 - Thor(SFML-Extension) Input Module tutorial: http://www.bromeon.ch/libraries/thor/tutorials/v2.0/actions.html
 - Doxygen Dokumentationssystem per Code-Kommentaren: http://www.doxygen.nl/manual/commands.html
*/

/* COMMENTING-STUFF
 - Comment member functions by using Multipline-Doxygen-Comments  @brief...
 - Comment member variables by using Single-Line too keep the class shorter
 */

/* INCLUDES
 - <> includes vor "" includes
 - Sind mit einer Leerzeile voneinander getrennt.
 - AUSNAHME: In cpp Files steht der include des entsprechenden h Files immer ganz oben abgetrennt mit einer Leerzeile.
 - Nur das benoetigte includieren.
*/

/* SUBLIME EDITOR
 - STRG + SHIFT + P: "install package control" (Ist das installiert, koennen Packages/Erweiterungen fuer Sublime installiert werden.)
 - STRG + SHIFT + P: "install package -> DoxyDoxygen" (Installiert Doxygen Dokumentationssystem)
*/

int main()
{
	/*Game g{ "ProjectSpace" };
	g.start();*/

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Vertex Test");
	
	sf::Vertex vertices[] =
	{
		sf::Vertex{sf::Vector2f{100, 100}, sf::Color::Red, sf::Vector2f{0, 0}},
		sf::Vertex{sf::Vector2f{200, 100}, sf::Color::Green, sf::Vector2f{0, 0}},
		sf::Vertex{sf::Vector2f{100, 200}, sf::Color::Blue, sf::Vector2f{0, 0}},
	};

	sf::Clock clock{};
	std::string strFrameTime{ "" };
	float frameTime = 0;
	int counter = 0;
	while (window.isOpen())
	{
		frameTime = clock.restart().asSeconds();

		strFrameTime.append("frameTime: ");
		strFrameTime.append(std::to_string(frameTime));
		strFrameTime.append(" ");
		strFrameTime.append("fps: ");
		strFrameTime.append(std::to_string(1.0f / frameTime));
		strFrameTime.append("\n");

		if (counter == 10)
		{
			std::cout << strFrameTime;
			strFrameTime.clear();
			counter = 0;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		window.clear();
		window.draw(vertices, 3, sf::PrimitiveType::Triangles);
		window.display();

		++counter;
	}

	std::cout << "Enter to continue ..." << std::endl;
	std::cin.get();
	return 0;
}