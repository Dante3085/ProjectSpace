
#include "Game.h"
#include "Util.h"

using namespace ProjectSpace;

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

 - ExpandMenu Buttonreihenfolge in oberster VBox zufaellig vertauscht

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
	Game g{ "ProjectSpace", WindowStyle::FULLSCREEN };
	g.start();

	return 0;
}