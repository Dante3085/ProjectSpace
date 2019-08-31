TODO: Ideen und Dinge, die ich umsetzen will.

 - Das gesamte Projekt �berdenken. Interklassenstruktur. Struktur einzelner Klassen. Welche Dinge ben�tige ich eigentlich. Was ist eigentlich mein Zielzustand. Konkrete Idee eines nicht unbedingt fertigen Zustand des Spiels, aber Meilensteins.

 - Speicherverwaltung

 - RessourceHandler (Laden von Texturen Audio bzw. externen Ressourcen)

 - Event System

 - Audio

 - Save / Load

 - TextBox

 - Fix Camera

 - (Vorschlag) Aufteilung der Quelldateien in Unterordner. Die Klassen "Animation" und "AnimatedSprite" in Ordner "Sprites".
   Die Klassen "Textbox", "Button", ... in den Ordner GUI. Darueber kann man sich im Team nochmal unterhalten.

 - Problem mit Button MouseEnter/MouseExit, wenn Fenster auf Monitor mit anderer Aufloesung verschoben wird.

 - In-Game-Console: Waehrend das Spiel laeuft Code eingeben und sachen veraendern.

 - Das gesamte Programm ruckelt in regelmaessigen Abstaenden.

 - Menue Buttons per Controller steuern k�nnen.

 - BattleOrder Anzeige (Vergleiche Final Fantasy 10)

 - Collision Detection: Unterscheiden, mit was kollidiert wurde (Mauer => Charakter stoppen; Sumpf => Charakter verlangsamen; ...)

 - Line2D: intersects(Line2D) Funktion, anstatt mit operator==

 - Util::FloatRect operator<<

 - Separating Axis Theorem for Collision Detection

 - Problem: Pointer vs C++-Reference: Beides ist in diesem Projekt inkonsistent verwendent.

 - KnightSprite schlanker machen.

 - Seperating Axis Theorem.

 - Pufferbereich in Kollision, um Kollision nicht st�ndig auszul�sen.

 - View Kamera

 - Men�, dass sich auf ver�nderndem View der Kamera immer an derselben Stelle �ffnet und schlie�t.
   (Camera View abh�ngige Elemente, nicht Default View abh�ngig)

 - Schnelleres Kompilieren: Trennung auf h und cpp (Bedarfsgerechtes Kompilieren mit make)

 - automatic makefile.

 - InputHandler
   - ::isKeyPressed() Name macht den Eindruck als ob der wirklich aktuelle Drueckzustand eines Buttons abgerufen wird.
     Dabei ist es der letzte gespeicherte. Das ist etwas uneindeutig.

   - Aufwand, um auf einmaligen key press zu checken ist zu gro�. Store Key State vor handler function.
     In handler function auf vorher nicht, jetzt schon gedr�ckt pr�fen und am Ende der handler function key Key State
     speichern.

   - InputHandling �berdenken: Globaler InputHandler auf dem InputEvents registriert werden k�nnen.

 - Window der Anwedung global verf�gbar machen, damit nicht immer �ber Parameter �bergeben werden muss.
   Andererseits signalisiert der Parameter die Absicht vern�nftig

 - Camera beim Scene-Wechsel irgendwie resetten, da Kameraeinstellung von der Camera einer Scene in der naechsten Scene bestehen bleibt,
 die Camera aber nicht mehr geupdatet wird.

 - ExpandMenu Buttonreihenfolge in oberster VBox zufaellig vertauscht

 - Final Fantasy 7 Textvariation:
 	- Text in Textbox: Normale Leute sprechen
 	- Wei�er Text ohne Textbox: Gedanken eines Charakters
 	- Grauer Text ohne Textbox: Charakter h�rt andere Stimme in Gedanken/Kopf.

 - Graph Plotter: Graphen im Spiel zum Debuggen anzeigen.
 - Debug Drawing: Im Spiel zum Debuggen primitive Geometrie einfach zeichnen k�nnen (Linien, Punkte, Dreiecke, ...)
 - Log Archive functionality to store certain logs longer and protect them from being deleted.

 - TranslateAnimation: Smoothe Hin- und Zur�ckanimation innerhalb der Klasse l�sen. Jetzt durch setzen der Startposition
   auf aktuelle Position des Men�elements au�erhalb der Klasse in globalem InputHandler.

 - Graphics Settings f�r RenderWindow in settings.ini speichern und beim Starten des Programms einfach laden => Mehrere Konstruktoren vermeiden.

 - Tilemap: 
   - file parsing with Regular Expressions.
   - addTile(name, pos, scale) Funktion und auch in loadFromFile() abfragen. Soll Tile an gegebener Position mit gegebenem
     Skalierungsfaktor anzeigen.

 - AnimatedSprite:
   - Problem: Anzeige des gesamten Spritesheets bevor das erste Mal auf das n�chste Frame gewechselt wird.
   - Enum zum hinzuf�gen von Animationen nicht unbedingt n�tig. String geht auch. Allerdings dann schwerer
     bei AnimatedSprite::setAnimation() herauszufinden, welche Animationen man setzen kann.

  - Animation:
    - W�hrend eine Animation abgespielt wird, tritt an immer derselben Stelle ein Ruckler auf.
	- Problem: Spritesheet hat viele Bilder, die viele verschiedene Animationen bilden k�nnen.
	  Allerdings kann ein Animationsobjekt nur gleichzeitig eine Animation speichern.
	  Folge ist, dass f�r verschiedene Animationen aus demselben Spritesheet mehrere Animationsobjekte
	  mit demselben Spritesheet erstellt werden m�ssen.

  - Button:
    - Textposition steuern k�nnen.
    - Buttongr��e an Text anpassen oder Text an Buttongr��e anpassen.
    - Textur �bergeben k�nnen.

  - std::vector<type> werden in einigen Teilen des Programms als Value �bergeben. Beispielsweise VBox, HBox
    Wenn sie als Referenz �bergeben werden, ist es aber nicht mehr m�glich den vector wie folgt zu �bergeben...
	... new VBox{{btn0, btn1, btn2}, ...}; Das hat irgendwas mit lValue, rValue zu tun. Vielleicht ist das
	Problem das es sich dann um einen tempor�ren, unbenannten Wert handelt.

  - #pragma once wegen anderen Compilern(z.B. g++ auf linux) rausschmei�en.