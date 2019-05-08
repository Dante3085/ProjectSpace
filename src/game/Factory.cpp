
#include "Factory.h"

#include <vector>
#include <iostream>
#include <SFML/Audio/Music.hpp>

#include "Tilemap.h"
#include "../menu/BattleMenu.h"
#include "../menu/TextBox.h"
#include "../menu/Button.h"
#include "../menu/VBox.h"
#include "../menu/HBox.h"
#include "../menu/BattleOrder.h"
#include "../menu/Portrait.h"
#include "../animation/FadeAnimation.h"
#include "../animation/TranslateAnimation.h"
#include "../animation/Animation.h"
#include "../animation/AnimatedSprite.h"
#include "../collision/CollisionManager.h"
#include "../collision/CollisionBox.h"
#include "../collision/CollisionShape.h"
#include "../rpg/Character.h"
#include "InputHandler.h"
#include "Camera.h"

namespace ProjectSpace
{
	Scene* Factory::CREATE_DEBUG_SCENE(sf::RenderWindow& window)
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

		AnimatedSprite * knightSprite = new AnimatedSprite{ sf::Vector2f{1000, 500}, 10 };
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

		FadeAnimation * fadeAnimation = new FadeAnimation{ knightSprite->getSprite(), 1000 };

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

		CollisionManager * collisionManager = new CollisionManager{ {knightSprite, triangle, triangle2, triangle3, triangle4, triangle5, triangle6, rectangle, smallDiamant, bigDiamant, threeDCube,
																   threeDCube2, threeDCube3} };

		BattleOrder * battleOrder = new BattleOrder
		{
			{
				new Character{15, 20, 3, 4}, new Character, new Character
			}, sf::Vector2f{400, 200}, 5, 5
		};

		InputHandler * inputHandler = new InputHandler{};
		inputHandler->add([knightSprite, &window, battleOrder, fadeAnimation]()
			{
				sf::Vector2f pos = knightSprite->getPosition();
				float speed = knightSprite->getSpeed();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					knightSprite->setAnimation(EAnimation::RIGHT);
					knightSprite->move(speed, 0);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					knightSprite->setAnimation(EAnimation::LEFT);
					knightSprite->move(-speed, 0);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					knightSprite->setAnimation(EAnimation::UP);
					knightSprite->move(0, -speed);
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					knightSprite->setAnimation(EAnimation::DOWN);
					knightSprite->move(0, speed);
				}

				else
				{
					knightSprite->setAnimation(EAnimation::IDLE);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					fadeAnimation->start();
				}
			});

		/*sf::Music* music = new sf::Music;

		if (!music->openFromFile("rsrc/marvin_track.ogg"))
		{
			std::cout << "Failed to load track" << std::endl;
		}
		music->setVolume(50);
		music->setLoop(true);

		Button* playMusicBtn = new Button{[music]()
		{
			music->play();
		}, window, "PlayMusic"};

		Button* pauseMusicBtn = new Button{[music]()
		{
			music->pause();
		}, window, "PauseMusic"};

		playMusicBtn->setPosition(0, 0);
		pauseMusicBtn->setPosition(playMusicBtn->getPosition() + sf::Vector2f{0, playMusicBtn->getHeight() + 5});*/

		BattleMenu * battleMenu = new BattleMenu{ sf::Vector2f{1000, 500}, inputHandler, window };

		scene->addEntities({ textBox, battleOrder, inputHandler, battleMenu, midnightSprite, knightSprite, fadeAnimation, collisionManager });

		scene->addDrawables({ backgroundSprite, knightSprite, battleOrder, battleMenu, triangle, triangle2, triangle3, triangle4, triangle5, triangle6, smallDiamant, bigDiamant, threeDCube,
							 threeDCube2, threeDCube3, rectangle, midnightSprite, textBox });

		return scene;
	}

	Scene * Factory::CREATE_DEBUG_SCENE_2(sf::RenderWindow & window)
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

	Scene* Factory::CREATE_TILEMAP_SCENE(sf::RenderWindow & window)
	{
		Scene* scene = new Scene();

		/*sf::Texture* left = new sf::Texture{};
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

		trees->loadFromFile("tilemaps/trees.txt");*/

		const int level[] =
		{
			0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
			0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
			0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
			0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
			2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
			0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
		};

		// create the tilemap from the level definition
		Tilemap* map = new Tilemap{};
		if (!map->load("rsrc/sfml-tileset.png", sf::Vector2u(32, 32), level, 16, 8))
		{
			std::cout << "@CREATE_TILEMAP_SCENE: Did not find Tilemap file." << std::endl;
		}

		scene->addDrawables({ map });

		return scene;
	}
}
