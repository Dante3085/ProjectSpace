
#include "Factory.h"

#include <vector>
#include <iostream>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
#include "MenuGroup.h"
#include "Tilemap.h"

namespace ProjectSpace
{
	Scene* Factory::create_debug_scene(sf::RenderWindow& window)
	{
		Scene* scene = new Scene(window);

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

		AnimatedSprite* midnightSprite = new AnimatedSprite{ sf::Vector2f{850, 850} };
		midnightSprite->addAnimation(EAnimation::IDLE, midnightAnim);
		midnightSprite->setAnimation(EAnimation::IDLE);
		midnightSprite->scale(1.2f, 1.2f);

		AnimatedSprite* knightSprite = new AnimatedSprite{ sf::Vector2f{1000, 500} };
		knightSprite->addAnimation(EAnimation::IDLE, knightIdleAnim);
		knightSprite->addAnimation(EAnimation::LEFT, knightLeftRunAnim);
		knightSprite->addAnimation(EAnimation::UP, knightUpRunAnim);
		knightSprite->addAnimation(EAnimation::RIGHT, knightRightRunAnim);
		knightSprite->addAnimation(EAnimation::DOWN, knightDownRunAnim);
		knightSprite->setAnimation(EAnimation::IDLE);


		// FadeAnimation* fadeAnimation = new FadeAnimation{ knightSprite->getSprite(), 255, 0, 1 };

		Camera* camera = new Camera{ *knightSprite, window, sf::Vector2f{200, 200} };

		CollisionBox* cb4 = new CollisionBox{ sf::Vector2f{200, 50}, sf::Vector2f{1950, 1500} };
		cb4->setCollisionType(CollisionType::WALL);
		cb4->setDrawBoundingBox(true);

		CollisionShape* triangle = new CollisionShape{ {sf::Vector2f{100, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle->setDrawBoundingBox(true);
		triangle->setCollisionType(CollisionType::WALL);

		CollisionShape* triangle2 = new CollisionShape{ {sf::Vector2f{150, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle2->setDrawBoundingBox(true);
		triangle2->setCollisionType(CollisionType::WALL);

		CollisionShape* triangle3 = new CollisionShape{ {sf::Vector2f{200, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle3->setDrawBoundingBox(true);
		triangle3->setCollisionType(CollisionType::WALL);

		CollisionShape* triangle4 = new CollisionShape{ {sf::Vector2f{300, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle4->setDrawBoundingBox(true);
		triangle4->setCollisionType(CollisionType::WALL);

		CollisionShape* triangle5 = new CollisionShape{ {sf::Vector2f{400, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle5->setDrawBoundingBox(true);
		triangle5->setCollisionType(CollisionType::WALL);

		CollisionShape* triangle6 = new CollisionShape{ {sf::Vector2f{500, 100}, sf::Vector2f{300, 300}, sf::Vector2f{100, 300}} };
		triangle6->setDrawBoundingBox(true);
		triangle6->setCollisionType(CollisionType::WALL);

		CollisionShape* rectangle = new CollisionShape{ {sf::Vector2f{500, 300}, sf::Vector2f{700, 300}, sf::Vector2f{700, 500}, sf::Vector2f{500, 500}} };
		rectangle->setDrawBoundingBox(true);
		rectangle->setCollisionType(CollisionType::WALL);

		CollisionShape* smallDiamant = new CollisionShape{ {sf::Vector2f{300, 700}, sf::Vector2f{400, 800}, sf::Vector2f{300, 900}, sf::Vector2f{200, 800}} };
		smallDiamant->setDrawBoundingBox(true);
		smallDiamant->setCollisionType(CollisionType::WALL);

		CollisionShape* bigDiamant = new CollisionShape{ {sf::Vector2f{1400, 600}, sf::Vector2f{1700, 900}, sf::Vector2f{1700, 1000}, sf::Vector2f{1400, 1300},
		sf::Vector2f{1100, 1000}, sf::Vector2f{1100, 900}} };
		bigDiamant->setDrawBoundingBox(true);
		bigDiamant->setCollisionType(CollisionType::WALL);

		CollisionShape* threeDCube = new CollisionShape{ {sf::Vector2f{2300, 600}, sf::Vector2f{2400, 500}, sf::Vector2f{2400, 700}, sf::Vector2f{2300, 800},
		sf::Vector2f{2300, 600}, sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2400, 500},
		sf::Vector2f{2400, 700}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800}, sf::Vector2f{2500, 600},
		sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800},
		sf::Vector2f{2300, 800}} };
		threeDCube->setDrawBoundingBox(true);
		threeDCube->setCollisionType(CollisionType::WALL);

		CollisionShape* threeDCube2 = new CollisionShape{ {sf::Vector2f{2500, 600}, sf::Vector2f{2400, 500}, sf::Vector2f{2400, 700}, sf::Vector2f{2300, 800},
		sf::Vector2f{2300, 600}, sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2400, 500},
		sf::Vector2f{2400, 700}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800}, sf::Vector2f{2500, 600},
		sf::Vector2f{2500, 600}, sf::Vector2f{2600, 500}, sf::Vector2f{2600, 700}, sf::Vector2f{2500, 800},
		sf::Vector2f{2300, 800}} };
		threeDCube2->setDrawBoundingBox(true);
		threeDCube2->setCollisionType(CollisionType::WALL);

		CollisionShape* threeDCube3 = new CollisionShape{ {sf::Vector2f{2800, 600}, sf::Vector2f{2400, 500}, sf::Vector2f{2400, 700}, sf::Vector2f{2300, 800},
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

		CollisionManager* collisionManager = new CollisionManager{ {windowBoundsBox, triangle,
			triangle2, triangle3, triangle4, triangle5, triangle6, smallDiamant, bigDiamant, threeDCube, threeDCube2, threeDCube3} };

		Button* expand0 = new Button
		{
			[]() {}, window, "expand0"
		};

		sf::Vector2f newSize{ 50, 50 };

		Button* expand00 = new Button
		{
			[]() {}, window, "e"
		};
		expand00->setSize(newSize);

		Button* expand01 = new Button
		{
			[]() {}, window, "e"
		};
		expand01->setSize(newSize);

		Button* expand1 = new Button
		{
			[]() {}, window, "expand1"
		};

		Button* expand2 = new Button
		{
			[]() {}, window, "expand2"
		};

		Button* expand3 = new Button
		{
			[]() {}, window, "expand3"
		};

		Button* groupBtn0 = new Button
		{
			[knightDownRunAnim]()
		{
		}, window, "GroupBtn0"
		};
		groupBtn0->setPosition(100, 100);

		Button* groupBtn1 = new Button
		{
			[]()
		{
		}, window, "GroupBtn1"
		};
		groupBtn1->setPosition(200, 200);

		Button* groupBtn2 = new Button
		{
			[]() {}, window, "GroupBtn1"
		};
		groupBtn2->setPosition(500, 600);

		MenuGroup* menuGroup = new MenuGroup{};
		menuGroup->addMenuElement(groupBtn1);
		menuGroup->addMenuElement(groupBtn2);

		InputHandler* inputHandler = new InputHandler{};

		inputHandler->storeKeyState(sf::Keyboard::Space, false);
		inputHandler->storeKeyState(sf::Keyboard::Up, false);
		inputHandler->add([inputHandler, menuGroup]()
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					menuGroup->move(0, -20);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					menuGroup->move(20, 0);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					menuGroup->move(0, 20);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					menuGroup->move(-20, 0);
				}
			});

		scene->addEntities({ inputHandler, collisionManager, menuGroup, groupBtn0 });

		scene->addDrawables({ backgroundSprite, windowBoundsBox, smallDiamant, bigDiamant, threeDCube,
			threeDCube2, threeDCube3, menuGroup, groupBtn0 });

		return scene;
	}

	Scene* Factory::create_empty_scene(sf::RenderWindow& window)
	{
		Scene* scene = new Scene(window);

		sf::Texture* background = new sf::Texture{};
		background->loadFromFile("rsrc/dark_castle_interior.png");

		sf::Sprite* backgroundSprite = new sf::Sprite{ *background };
		backgroundSprite->setScale(window.getSize().x / backgroundSprite->getLocalBounds().width,
			window.getSize().y / backgroundSprite->getLocalBounds().height);

		scene->addDrawables({ backgroundSprite });

		return scene;
	}

	Scene* Factory::create_tilemap_scene(sf::RenderWindow& window)
	{
		Scene* scene = new Scene(window);

		TileMap* t = new TileMap{"rsrc/SNES - Chrono Trigger - Court Room.gif"};
		t->loadFromFile("tilemaps/milestone1_tilemap.txt");

		Animation* cronoWalkDown = new Animation{"rsrc/CronoTransparentBackground.png"};
		cronoWalkDown->setAnimation({ sf::IntRect{130, 15, 15, 33}, {150, 17, 16, 31}, {171, 14, 17, 34},
									  {193, 15, 15, 33}, {213, 17, 16, 31} }, 0.5f);

		AnimatedSprite* crono = new AnimatedSprite{ sf::Vector2f{1000, 200}};
		crono->addAnimation(EAnimation::DOWN, cronoWalkDown);
		crono->setAnimation(EAnimation::DOWN);
		crono->setScale(10, 10);

		Character* c1 = new Character{};
		Character* c2 = new Character{};
		Character* c3 = new Character{};
		BattleOrder* battleOrder = new BattleOrder{ std::vector<Character*>{c1, c2, c3}, sf::Vector2f{200, 200} };

		Button* btn = new Button{ []()
		{
			std::cout << "I am a Button" << std::endl;
		}, window, "Button" };
		btn->setPosition(1000, 1000);

		sf::Vector2f btnPos = btn->getPosition();
		TranslateAnimation* ta = new TranslateAnimation{ *btn, btnPos, btnPos * 2, 1000 };

		using key = sf::Keyboard;
		InputHandler* inputHandler = new InputHandler{};
		inputHandler->storeKeyState(key::F, false);
		inputHandler->storeKeyState(key::B, false);
		inputHandler->storeKeyState(key::Space, false);
		inputHandler->add([ta, inputHandler, battleOrder]()
			{
				if (!inputHandler->wasKeyPressed(key::F) && key::isKeyPressed(key::F))
				{
					ta->setFrom(ta->getTranslatable().getPosition());
					ta->setTo(sf::Vector2f{ 1000, 1000 });
					ta->start();
				}
				else if (!inputHandler->wasKeyPressed(key::B) && key::isKeyPressed(key::B))
				{
					ta->setFrom(ta->getTranslatable().getPosition());
					ta->setTo(sf::Vector2f{ 1000, 500 });
					ta->start();
				}
				else if (!inputHandler->wasKeyPressed(key::Space) && key::isKeyPressed(key::Space))
				{
					battleOrder->cycle();
				}

				inputHandler->storeKeyState(key::F, key::isKeyPressed(key::F));
				inputHandler->storeKeyState(key::B, key::isKeyPressed(key::B));
				inputHandler->storeKeyState(key::Space, key::isKeyPressed(key::Space));
			});

		scene->addEntities({inputHandler, btn, ta, battleOrder, crono});
		scene->addDrawables({ t, btn, battleOrder, crono });

		return scene;
	}

	Scene* Factory::create_collision_scene(sf::RenderWindow& window)
	{
		Scene* scene = new Scene{window};

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

		Animation* facesAnimation = new Animation{ "rsrc/faces.png", 300, 500, 0, 0, 6, 0.5f };
		AnimatedSprite* facesSprite = new AnimatedSprite{ sf::Vector2f{1000, 1000} };
		facesSprite->addAnimation(EAnimation::IDLE, facesAnimation);
		facesSprite->setAnimation(EAnimation::IDLE);

		// Texturen
		sf::Texture* tex_background = new sf::Texture{};
		tex_background->loadFromFile("rsrc/background.png");
		sf::Sprite* background = new sf::Sprite{ *tex_background };
		background->setScale(window.getSize().x / background->getLocalBounds().width,
			window.getSize().y / background->getLocalBounds().height);

		// Collision-Geometrie
		sf::Vector2f window_size{ window.getSize() };
		CollisionBox* cb_background = new CollisionBox{ sf::Vector2f{(float)window_size.x, (float)window_size.y}, sf::Vector2f{0, 0} };
		cb_background->setCollisionType(CollisionType::WALL);

		CollisionShape* cs0 = new CollisionShape{ {sf::Vector2f{690, 0}, sf::Vector2f{1240, 0}, sf::Vector2f{1240, 130},
												   sf::Vector2f{800, 130}, sf::Vector2f{800, 590}, sf::Vector2f{690, 590}} };
		cs0->setCollisionType(CollisionType::WALL);
		cs0->setDrawBoundingBox(true);

		CollisionShape* cs1 = new CollisionShape{ {sf::Vector2f{800, 590}, sf::Vector2f{1130, 590}, sf::Vector2f{1130, 760}, sf::Vector2f{1190, 807},
												  sf::Vector2f{1115, 1060}, sf::Vector2f{1000, 1150}, sf::Vector2f{830, 1150}, sf::Vector2f{830, 1317},
												  sf::Vector2f{540, 1290}, sf::Vector2f{480, 1030}, sf::Vector2f{370, 1035}, sf::Vector2f{370, 917}} };
		cs1->setCollisionType(CollisionType::WALL);
		cs1->setDrawBoundingBox(true);

		CollisionManager* collision_manager = new CollisionManager{ {cb_background, cs0, cs1} };

		// Add Scene Entities
		scene->addEntities({ collision_manager, knightSprite, facesSprite });

		// Add Scene Drawables
		scene->addDrawables({ background, knightSprite, cs0, cs1, facesSprite });

		// ----------
		return scene;
	}

	Scene* Factory::create_menu_scene(sf::RenderWindow& window)
	{
		return nullptr;
	}
}
