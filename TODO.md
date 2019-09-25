TODO: Ideen und Dinge, die ich umsetzen will.

 - Das gesamte Projekt Überdenken. Interklassenstruktur. Struktur einzelner Klassen. Welche Dinge benötige ich eigentlich. Was ist eigentlich mein Zielzustand. Konkrete Idee eines nicht unbedingt fertigen Zustand des Spiels, aber Meilensteins.

 - Speicherverwaltung

 - RessourceHandler (Laden von Texturen Audio bzw. externen Ressourcen)

 - Event System

 - AudioCollection:
   - Manipulate Volume of all Sound Effects at the same time.

 - Save / Load

 - TextBox

 - Problem mit Button MouseEnter/MouseExit, wenn Fenster auf Monitor mit anderer Aufloesung verschoben wird.

 - In-Game-Console: Waehrend das Spiel laeuft Code eingeben und sachen veraendern.

 - Das gesamte Programm ruckelt in regelmaessigen Abstaenden.

 - ButtonMenu:
   - Per Controller steuern können
   - Cursor Texture(Fingerzeiger in FinalFantasy)

 - BattleOrder Anzeige (Vergleiche Final Fantasy 10)

 - Collision Detection: 
   - Kollisionsarten mit benutzerdefinierten Reaktionen ermöglichen (WALL => Stopp, POISON => Damage)
   - Kollisionsschichten:
     1. Per Grid oder Octtree wird erst überprüft, welche Collidables für eine Kollision überhaupt in
	      Frage kommen. Das heißt, Grid oder Octree teilen die Spielwelt in abgesteckte Areale auf. 
		    Es können nur Collidables miteinander kollidieren, die im selben Areal sind.
	   2. Nachdem beschlossen ist, dass zwei Collidables im selben Areal sind, wird auf Sphere- oder
	      Rectangle Collision geprüft.
	   3. Nachdem beschlossen ist, dass die Spheres oder Rectangles(auch Sphere mit Rectangle) der beiden
	      Collidables miteinander kollidieren, wird auf PixelPerfectCollision geprüft.
   - https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection

 - Problem: Pointer vs C++-Reference: Beides ist in diesem Projekt inkonsistent verwendent.

 - KnightSprite schlanker machen.

 - Seperating Axis Theorem.

 - Pufferbereich in Kollision, um Kollision nicht ständig auszulösen.

 - Camera
   - Menü soll sich immer an derselben Stelle relativ zum View öffnen.
   - Einstellmöglichkeit bei setTranslatable() einen mit Easing unterstzützen Fokuswechsel zu machen(Kameraschwenk).

 - Schnelleres Kompilieren: Trennung auf h und cpp (Bedarfsgerechtes Kompilieren mit make)

 - InputSystem
   - New InputSystem: https://www.gamedev.net/blogs/entry/2250186-designing-a-robust-input-handling-system-for-games/
                      https://github.com/grimtraveller/scribblings-by-apoch
   - BUG: Wenn mehrere Keys auf die selbe Action gemappt werden, kann es sein, dass die Aktion gar nicht auslöst,
     weil der nicht gedrückte Key die Action immer auf false setzt.


 - Window der Anwedung global verfügbar machen, damit nicht immer über Parameter übergeben werden muss.
   Andererseits signalisiert der Parameter die Absicht vernünftig

 - ExpandMenu Buttonreihenfolge in oberster VBox zufaellig vertauscht

 - Final Fantasy 7 Textvariation:
 	- Text in Textbox: Normale Leute sprechen
 	- Weißer Text ohne Textbox: Gedanken eines Charakters
 	- Grauer Text ohne Textbox: Charakter hört andere Stimme in Gedanken/Kopf.

 - Graph Plotter: Graphen im Spiel zum Debuggen anzeigen.
 - Debug Drawing: Im Spiel zum Debuggen primitive Geometrie einfach zeichnen können (Linien, Punkte, Dreiecke, ...)
 - Log Archive functionality to store certain logs longer and protect them from being deleted.

 - TranslateAnimation: Smoothe Hin- und Zurückanimation innerhalb der Klasse lösen. Jetzt durch setzen der Startposition
   auf aktuelle Position des Menüelements außerhalb der Klasse in globalem InputHandler.

 - Graphics Settings für RenderWindow in settings.ini speichern und beim Starten des Programms einfach laden => Mehrere Konstruktoren vermeiden.

 - Tilemap: 
   - file parsing with Regular Expressions.
   - addTile(name, pos, scale) Funktion und auch in loadFromFile() abfragen. Soll Tile an gegebener Position mit gegebenem
     Skalierungsfaktor anzeigen.

 - AnimatedSprite:
   - Problem: Anzeige des gesamten Spritesheets bevor das erste Mal auf das nächste Frame gewechselt wird.
   - Enum zum hinzufügen von Animationen nicht unbedingt nötig. String geht auch. Allerdings dann schwerer
     bei AnimatedSprite::setAnimation() herauszufinden, welche Animationen man setzen kann.

  - Animation:
    - Während eine Animation abgespielt wird, tritt an immer derselben Stelle ein Ruckler auf.
	- Problem: Spritesheet hat viele Bilder, die viele verschiedene Animationen bilden können.
	  Allerdings kann ein Animationsobjekt nur gleichzeitig eine Animation speichern.
	  Folge ist, dass für verschiedene Animationen aus demselben Spritesheet mehrere Animationsobjekte
	  mit demselben Spritesheet erstellt werden müssen.

  - Button:
    - Textposition steuern können.
    - Buttongröße an Text anpassen oder Text an Buttongröße anpassen.
    - Textur übergeben können.

  - std::vector<type> werden in einigen Teilen des Programms als Value übergeben. Beispielsweise VBox, HBox
    Wenn sie als Referenz übergeben werden, ist es aber nicht mehr möglich den vector wie folgt zu übergeben...
	... new VBox{{btn0, btn1, btn2}, ...}; Das hat irgendwas mit lValue, rValue zu tun. Vielleicht ist das
	Problem das es sich dann um einen temporären, unbenannten Wert handelt.

  - ScrollText
    - Horizontal scrollender Text, der ab bestimmter Grenze wieder am Anfang weiterscrollt.
	- https://www.youtube.com/watch?v=e_pY-uGkDFA

  - Entity doUpdate Variable und Entity::update() checkt, ob doUpdate true ist.
    Zentrale Stelle, um der Entity das updaten zu verbieten.