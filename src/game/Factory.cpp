
#include "Factory.h"

#include <vector>
#include <iostream>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Tilemap.h"
#include "ExpandMenu.h"
#include "BattleMenu.h"
#include "TextBox.h"
#include "Button.h"
#include "VBox.h"
#include "HBox.h"
#include "BattleOrder.h"
#include "Portrait.h"
#include "FadeAnimation.h"
#include "TranslateAnimation.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "CollisionManager.h"
#include "CollisionBox.h"
#include "CollisionShape.h"
#include "Character.h"
#include "InputHandler.h"
#include "Camera.h"

namespace ProjectSpace
{
	Scene* Factory::create_debug_scene(sf::RenderWindow& window)
	{
		Scene* scene = new Scene();

		Animation* spellAnim = new Animation{ "rsrc/1_magicspell_spritesheet.png", 100, 100, 0, 0, 75, 0.05f };
		Animation* magicAnim = new Animation{ "rsrc/2_magic8_spritesheet.png", 100, 100, 0, 0, 61, 0.05f };
		Animation* weaponHitAnim = new Animation{ "rsrc/10_weaponhit_spritesheet.png", 100, 100, 0, 0, 61, 0.05f };
		Animation* fireAnim = new Animation{ "rsrc/9_brightfire_spritesheet.png", 100, 100, 0, 0, 61, 0.05f };
		Animation* midnightAnim = new Animation{ "rsrc/18_midnight_spritesheet.png", 100, 100, 0, 0, 61, 0.05f };

		Animation* knightIdleAnim = new Animation{ "rsrc/knight_idle.png", 84, 84, 0, 0, 4, 0.15f };
		Animation* knightLeftRunAnim = new Animation{ "rsrc/knight_left_run.png", 84, 84, 0, 0, 6, 0.1f };
		Animation* knightUpRunAnim = new Animation{ "rsrc/knight_up_run.png", 84, 84, 0, 0, 5, 0.1f };
		Animation* knightRightRunAnim = new Animation{ "rsrc/knight_right_run.png", 84, 84, 0, 0, 6, 0.1f };
		Animation* knightDownRunAnim = new Animation{ "rsrc/knight_down_run.png", 84, 84, 0, 0, 5, 0.1f };

		sf::Texture* background = new sf::Texture{};
		background->loadFromFile("rsrc/cyberpunk-street.png");

		TextBox* textBox = new TextBox{ "rsrc/blueBackground.png", "Das ist ein laengerer TestText. Bla dasdsad dasdddddddddddddddddddddddddddddd ddddddddddddddddddddddddddasddddddddddd dddddddddddddddddddddddddddddddddddddddddddddasd dddddddddddddddddddddddddddddddddddddddddddddddddddddddasdddddddddddddd ddddddddddddddddddddddddddddddddddddddddd",
		sf::Vector2f{1000, 1000}, sf::Vector2f{100, 1750} };
		textBox->setOpacity(200);
		textBox->setPadding(50);

		sf::Sprite* backgroundSprite = new sf::Sprite{ *background };
		backgroundSprite->setScale(window.getSize().x / backgroundSprite->getLocalBounds().width,
			window.getSize().y / backgroundSprite->getLocalBounds().height);

		/*AnimatedSprite* spellSprite = new AnimatedSprite{223, 80};
		spellSprite->addAnimation(EAnimation::IDLE, spellAnim);
		spellSprite->setAnimation(EAnimation::IDLE);
		spellSprite->scale(0.5f, 0.5f);

		AnimatedSprite* magicSprite = new AnimatedSprite{100, 810};
		magicSprite->addAnimation(EAnimation::IDLE, magicAnim);
		magicSprite->setAnimation(EAnimation::IDLE);

		AnimatedSprite* weaponHitSprite = new AnimatedSprite{200, 760};
		weaponHitSprite->addAnimation(EAnimation::IDLE, weaponHitAnim);
		weaponHitSprite->setAnimation(EAnimation::IDLE);

		AnimatedSprite* fireSprite = new AnimatedSprite{322, 760};
		fireSprite->addAnimation(EAnimation::IDLE, fireAnim);
		fireSprite->setAnimation(EAnimation::IDLE);
		fireSprite->setDrawBoundingBox(true);
		fireSprite->setCollisionType(CollisionType::ATTACK);*/

		AnimatedSprite * midnightSprite = new AnimatedSprite{ sf::Vector2f{850, 850} };
		midnightSprite->addAnimation(EAnimation::IDLE, midnightAnim);
		midnightSprite->setAnimation(EAnimation::IDLE);
		midnightSprite->scale(1.2f, 1.2f);
		midnightSprite->setDrawBoundingBox(true);

		AnimatedSprite * knightSprite = new AnimatedSprite{ sf::Vector2f{1000, 500} };
		knightSprite->addAnimation(EAnimation::IDLE, knightIdleAnim);
		knightSprite->addAnimation(EAnimation::LEFT, knightLeftRunAnim);
		knightSprite->addAnimation(EAnimation::UP, knightUpRunAnim);
		knightSprite->addAnimation(EAnimation::RIGHT, knightRightRunAnim);
		knightSprite->addAnimation(EAnimation::DOWN, knightDownRunAnim);
		knightSprite->setAnimation(EAnimation::IDLE);
		knightSprite->setDrawBoundingBox(true);

		knightSprite->setCollisionHandler([knightSprite](Collidable* partner)
		{
			if (partner->getCollisionType() == CollisionType::WALL)
			{
				knightSprite->setPosition(knightSprite->getPreviousPosition());
			}
		});

		Character* knight = new Character{*knightSprite};

		FadeAnimation * fadeAnimation = new FadeAnimation{ knightSprite->getSprite(), 255, 0, 1};

		Camera * camera = new Camera{ *knightSprite, window, sf::Vector2f{200, 200} };

		CollisionBox * cb4 = new CollisionBox{ sf::Vector2f{200, 50}, sf::Vector2f{1950, 1500} };
		cb4->setCollisionType(CollisionType::WALL);
		cb4->setDrawBoundingBox(true);

		CollisionShape * triangle = new CollisionShape{ {sf::Vector2f{100, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle->setDrawBoundingBox(true);
		triangle->setCollisionType(CollisionType::WALL);

		CollisionShape * triangle2 = new CollisionShape{ {sf::Vector2f{150, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle2->setDrawBoundingBox(true);
		triangle2->setCollisionType(CollisionType::WALL);

		CollisionShape * triangle3 = new CollisionShape{ {sf::Vector2f{200, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle3->setDrawBoundingBox(true);
		triangle3->setCollisionType(CollisionType::WALL);

		CollisionShape * triangle4 = new CollisionShape{ {sf::Vector2f{300, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle4->setDrawBoundingBox(true);
		triangle4->setCollisionType(CollisionType::WALL);

		CollisionShape * triangle5 = new CollisionShape{ {sf::Vector2f{400, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle5->setDrawBoundingBox(true);
		triangle5->setCollisionType(CollisionType::WALL);

		CollisionShape * triangle6 = new CollisionShape{ {sf::Vector2f{500, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle6->setDrawBoundingBox(true);
		triangle6->setCollisionType(CollisionType::WALL);

		CollisionShape * rectangle = new CollisionShape{ {sf::Vector2f{500, 300}, sf::Vector2f{700, 300}, sf::Vector2f{700, 500}, sf::Vector2f{500, 500}} };
		rectangle->setDrawBoundingBox(true);
		rectangle->setCollisionType(CollisionType::WALL);

		CollisionShape * smallDiamant = new CollisionShape{ {sf::Vector2f{300, 700}, sf::Vector2f{400, 800}, sf::Vector2f{300, 900}, sf::Vector2f{200, 800}} };
		smallDiamant->setDrawBoundingBox(true);
		smallDiamant->setCollisionType(CollisionType::WALL);

		CollisionShape * bigDiamant = new CollisionShape{ {sf::Vector2f{1400, 600}, sf::Vector2f{1700, 900}, sf::Vector2f{1700, 1000}, sf::Vector2f{1400, 1300},
		sf::Vector2f{1100, 1000}, sf::Vector2f{1100, 900}} };
		bigDiamant->setDrawBoundingBox(true);
		bigDiamant->setCollisionType(CollisionType::WALL);

		CollisionShape * threeDCube = new CollisionShape{ {sf::Vector2f{2300, 600}, sf::Vector2f{2400, 500}, sf::Vector2f{2400, 700}, sf::Vector2f{2300, 800},
		sf::Vector2f{2300, 600}, sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2400, 500},
		sf::Vector2f{2400, 700}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800}, sf::Vector2f{2500, 600},
		sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800},
		sf::Vector2f{2300, 800}} };
		threeDCube->setDrawBoundingBox(true);
		threeDCube->setCollisionType(CollisionType::WALL);

		CollisionShape * threeDCube2 = new CollisionShape{ {sf::Vector2f{2500, 600}, sf::Vector2f{2400, 500}, sf::Vector2f{2400, 700}, sf::Vector2f{2300, 800},
		sf::Vector2f{2300, 600}, sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2400, 500},
		sf::Vector2f{2400, 700}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800}, sf::Vector2f{2500, 600},
		sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800},
		sf::Vector2f{2300, 800}} };
		threeDCube2->setDrawBoundingBox(true);
		threeDCube2->setCollisionType(CollisionType::WALL);

		CollisionShape * threeDCube3 = new CollisionShape{ {sf::Vector2f{2800, 600}, sf::Vector2f{2400, 500}, sf::Vector2f{2400, 700}, sf::Vector2f{2300, 800},
		sf::Vector2f{2300, 600}, sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2400, 500},
		sf::Vector2f{2400, 700}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800}, sf::Vector2f{2500, 600},
		sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800},
		sf::Vector2f{2300, 800}} };
		threeDCube3->setDrawBoundingBox(true);
		threeDCube3->setCollisionType(CollisionType::WALL);

		sf::Vector2u windowSize{ window.getSize() };
		CollisionBox* windowBoundsBox = new CollisionBox{ sf::Vector2f{(float)windowSize.x, (float)windowSize.y}, sf::Vector2f{0, 0} };
		windowBoundsBox->setCollisionType(CollisionType::WALL);
		windowBoundsBox->setDrawBoundingBox(true);

		CollisionManager* collisionManager = new CollisionManager{ {windowBoundsBox, knightSprite, triangle, 
			triangle2, triangle3, triangle4, triangle5, triangle6, smallDiamant, bigDiamant, threeDCube, threeDCube2, threeDCube3} };

		InputHandler * inputHandler = new InputHandler{};

		inputHandler->storeKeyState(sf::Keyboard::Space, false);
		inputHandler->add([fadeAnimation, inputHandler]()
		{
			/*if (!inputHandler->wasKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				fadeAnimation->start();
			}

			inputHandler->storeKeyState(sf::Keyboard::Space, sf::Keyboard::isKeyPressed(sf::Keyboard::Space));*/
		});

		Button* expand0 = new Button
		{
			[](){}, window, "expand0"
		};

		sf::Vector2f newSize{ 50, 50 };

		Button* expand00 = new Button
		{
			[](){}, window, "e"
		};
		expand00->setSize(newSize);

		Button* expand01 = new Button
		{
			[](){}, window, "e"
		};
		expand01->setSize(newSize);

		Button* expand1 = new Button
		{
			[](){}, window, "expand1"
		};

		Button* expand2 = new Button
		{
			[](){}, window, "expand2"
		};

		Button* expand3 = new Button
		{
			[](){}, window, "expand3"
		};		

		ExpandMenu* expandMenu = new ExpandMenu
		{ 
			{
				{expand0, {expand00, expand01}},
				{expand1, {}},
				{expand2, {}},
				{expand3, {}}
			}, sf::Vector2f{200, 100}, inputHandler
		};

		BattleMenu* battleMenu = new BattleMenu{ sf::Vector2f{1000, 500}, inputHandler, window };

		scene->addEntities({ inputHandler, knight, collisionManager, expandMenu, fadeAnimation });

		scene->addDrawables({ backgroundSprite, knight, expandMenu, windowBoundsBox, smallDiamant, bigDiamant, threeDCube, 
			threeDCube2, threeDCube3 });

		return scene;
	}

	Scene* Factory::create_empty_scene(sf::RenderWindow & window)
	{
		Scene* scene = new Scene();

		sf::Texture* background = new sf::Texture{};
		background->loadFromFile("rsrc/dark_castle_interior.png");

		sf::Sprite* backgroundSprite = new sf::Sprite{ *background };
		backgroundSprite->setScale(window.getSize().x / backgroundSprite->getLocalBounds().width,
			window.getSize().y / backgroundSprite->getLocalBounds().height);

		scene->addDrawables({ backgroundSprite });

		return scene;
	}

	Scene* Factory::create_tilemap_scene(sf::RenderWindow & window)
	{
		Scene* scene = new Scene();

		sf::Texture* left = new sf::Texture{};
		left->loadFromFile("rsrc/generic-rpg/tiles/left-tile.png");

		sf::Texture* topLeftCorner = new sf::Texture{};
		topLeftCorner->loadFromFile("rsrc/generic-rpg/tiles/top-left-tile.png");

		sf::Texture* top = new sf::Texture{};
		top->loadFromFile("rsrc/generic-rpg/tiles/top-tile.png");

		sf::Texture* topRightCorner = new sf::Texture{};
		topRightCorner->loadFromFile("rsrc/generic-rpg/tiles/top-right-tile.png");

		sf::Texture* right = new sf::Texture{};
		right->loadFromFile("rsrc/generic-rpg/tiles/right-tile.png");

		sf::Texture* bottomRightCorner = new sf::Texture{};
		bottomRightCorner->loadFromFile("rsrc/generic-rpg/tiles/bottom-right-tile.png");

		sf::Texture* bottom = new sf::Texture{};
		bottom->loadFromFile("rsrc/generic-rpg/tiles/bottom-tile.png");

		sf::Texture* bottomLeftCorner = new sf::Texture{};
		bottomLeftCorner->loadFromFile("rsrc/generic-rpg/tiles/bottom-left-tile.png");

		sf::Texture* blank = new sf::Texture{};
		blank->loadFromFile("rsrc/generic-rpg/tiles/generic-rpg-tile71.png");

		Tilemap* ground = new Tilemap{ sf::Vector2f{0, 0}, sf::Vector2f{64, 64}, std::map<char, sf::Texture*>
		{
			{'0', left},
			{'1', topLeftCorner},
			{'2', top},
			{'3', topRightCorner},
			{'4', right},
			{'5', bottomRightCorner},
			{'6', bottom},
			{'7', bottomLeftCorner},
			{'8', blank},
		} };

		ground->loadFromFile("tilemaps/ground.txt");

		sf::Texture* tree = new sf::Texture{};
		tree->loadFromFile("rsrc/generic-rpg/props_decorations/generic-rpg-tree01.png");

		Tilemap* trees = new Tilemap{ sf::Vector2f{0, 0}, sf::Vector2f{100, 160}, std::map<char, sf::Texture*>
		{
			{'t', tree},
		} };

		trees->loadFromFile("tilemaps/trees.txt");

		/*// create the tilemap from the level definition
		Tilemap* map = new Tilemap{};
		map->load("rsrc/TilesetGrass/overworld_tileset_grass.png", sf::Vector2u{ 16, 16 }, "tilemaps/ground.txt", 192, 336);*/

		scene->addDrawables({ ground, trees });

		return scene;
	}

	Scene* Factory::create_collision_scene(sf::RenderWindow& window)
	{
		Scene* scene = new Scene{};

		// Spielercharakter
		Animation* knightIdleAnim = new Animation{ "rsrc/knight_idle.png", 84, 84, 0, 0, 4, 0.15f };
		Animation* knightLeftRunAnim = new Animation{ "rsrc/knight_left_run.png", 84, 84, 0, 0, 6, 0.1f };
		Animation* knightUpRunAnim = new Animation{ "rsrc/knight_up_run.png", 84, 84, 0, 0, 5, 0.1f };
		Animation* knightRightRunAnim = new Animation{ "rsrc/knight_right_run.png", 84, 84, 0, 0, 6, 0.1f };
		Animation* knightDownRunAnim = new Animation{ "rsrc/knight_down_run.png", 84, 84, 0, 0, 5, 0.1f };

		AnimatedSprite* knightSprite = new AnimatedSprite{ sf::Vector2f{900, 220} };
		knightSprite->addAnimation(EAnimation::IDLE, knightIdleAnim);
		knightSprite->addAnimation(EAnimation::LEFT, knightLeftRunAnim);
		knightSprite->addAnimation(EAnimation::UP, knightUpRunAnim);
		knightSprite->addAnimation(EAnimation::RIGHT, knightRightRunAnim);
		knightSprite->addAnimation(EAnimation::DOWN, knightDownRunAnim);
		knightSprite->setAnimation(EAnimation::IDLE);
		knightSprite->setDrawBoundingBox(true);

		knightSprite->setCollisionHandler([knightSprite](Collidable * partner)
			{
				if (partner->getCollisionType() == CollisionType::WALL)
				{
					knightSprite->setPosition(knightSprite->getPreviousPosition());
				}
			});

		Character* knight = new Character{ *knightSprite };

		// Texturen
		sf::Texture* tex_background = new sf::Texture{};
		tex_background->loadFromFile("rsrc/background.png");
		sf::Sprite* background = new sf::Sprite{*tex_background};
		background->setScale(window.getSize().x / background->getLocalBounds().width,
			window.getSize().y / background->getLocalBounds().height);

		// Collision-Geometrie
		sf::Vector2f window_size{ window.getSize() };
		CollisionBox* cb_background = new CollisionBox{sf::Vector2f{(float)window_size.x, (float)window_size.y}, sf::Vector2f{0, 0}};
		cb_background->setCollisionType(CollisionType::WALL);

		CollisionBox* cs0 = new CollisionBox{ sf::Vector2f{850, 0}, sf::Vector2f{400, 135} };
		cs0->setCollisionType(CollisionType::WALL);
		cs0->setDrawBoundingBox(true);

		CollisionBox* cs1 = new CollisionBox{ sf::Vector2f{380, 0}, sf::Vector2f{470, 800} };
		cs1->setCollisionType(CollisionType::WALL);
		cs1->setDrawBoundingBox(true);

		CollisionManager* collision_manager = new CollisionManager{ {cb_background, knightSprite, cs0, cs1} };

		// Add Scene Entities
		scene->addEntities({ collision_manager, knight });

		// Add Scene Drawables
		scene->addDrawables({background, knight, cs0, cs1 });

		// ----------
		return scene;
	}

	Scene* Factory::create_menu_scene(sf::RenderWindow& window)
	{
		return nullptr;
	}

	ExpandMenu* create_combat_menu()
	{
		// TODO(moritz):
		return nullptr;
	}
}
