
- AnimatedSprite:
  - KEEP
  - Delegating to all sf::Sprite functions by creating functions of the same name 
    that just call the respective sf::Sprite function with the given arguments seems bad(Code smell).
  - Things regarding collision(previousPosition, layerCollidable) or any other thing
    that isn't Animation should be kept out of the AnimatedSprite class(single responsibility).
  - sf::Sprite nicht benutzen und eigene Implementation mit sf::Vertex versuchen.

- Animation:
  - TBD
  - Warum muss diese Klasse separat von AnimatedSprite existieren ?
  - Verpackung von SpriteSheet, frames und frameDelay in einer Einheit.
  - Nachteil ist momentan, dass mehrere Animationen von einem Spritesheet
    mehrere Animation Objekte benötigen, da ein Animation Objekt nur eine
    Animation enthalten kann.
  - Mehrere Animationen eines Spritesheets in einem Animationsobjekt speichern.
  - Mehrere uniforme Frames mit und ohne spacing automatisiert speichern können.

- FadeAnimation:
  - TBD
  - Fadeable Interface: Alle Sachen, die man faden kann, müssen setColor() implementieren.

- TranslateAnimation:
  - TBD
  - Mit Interface lösen (sf::Transformable, Translatable)

- Translatable:
  - NEW: Interface for 2d moveable things.
  - Should maybe have getBounds(): sf::FloatRect

- Easer:
  - TRASH
  - Schrittweises übersetzen von einem Startwert zu einem Endwert.
  - int, float, double
  - Vector2<int>, Vector2<float>, Vector2<double>
  - Funktioniert nicht: Verletzung des Geheimnisprinzip(Kein Zugriff auf private Werte jeglicher Klassen),
    Easable Interface würde Template Parameter aufgrund verschiedener Werte verlangen (int, sf::Vector)

- Easing.h:
  - KEEP
  - Problem mit mehreren Definitionen der selben Funktion in verschiedenen Translation Units(One-Definition-Rule Verletzung).
    Sachen, die im globalen scope oder in einem namespace-scope stehen haben standardmäßig external linkage. Das heißt sie können
    nicht nur in ihrer eigenen, sondern auch in fremden Translation Units verwendet werden. Da die Funktionsdefinitionen in Easing.h
    vorhanden sind, wird der Linker im Fall, dass Easing.h in mehr als einer Translation Unit verwendet wird, auf mehrere Definitionen
    für ein und dieselbe Funktion treffen. Das darf nicht sein !
  - Lösung: Funktionsdeklarationen in .h-Datei und Funktionsdefinitionen in .cpp-Datei.

- Util.h
  - KEEP
  - Gleiches Problem, wie bei Easing.h
  - Umbenennung in MathUtil or VectorUtil.

- InputManager
  - NEW
  - Store states of all keys each frame, so that onKeyDown is easy to implement inside InputManager.
    Current solution is that user has to manually store required key state to check if it was down 
    last frame or not.

- New Folder Structure:
  - animation
    - Animation
    - AnimatedSprite
    - TranslateAnimation
    - Translatable
    - FadeAnimation
    - Fadeable
  - collision
    - Collidable
    - CollisionBox
    - CollisionManager
    - CollisionShape
    - LayerCollidable
    - Line2D
    - Line2F
  - gui(Graphical User Interface)
    - MenuElement
    - MenuGroup
    - VBox
    - HBox
    - Button
    - ButtonMenu
    - BattleMenu
    - BattleOrder
    - ExpandMenu
    - Slider
    - TextBox
  - scenes
    - ChronoTriggerScene
    - DebugScene
    - EScene
    - Scene
  - rpg
    - Character
    - Item
    - Weapon
    - Armor
    - Magic
    - Skill