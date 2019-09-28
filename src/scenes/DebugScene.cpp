
#include "scenes/DebugScene.h"

namespace ProjectSpace
{
    DebugScene::DebugScene(sf::RenderWindow &window)
        : Scene{ window },
          animMagicSpell{"rsrc/spritesheets/1_magicspell_spritesheet.png", 100, 100, 0, 0, 75, 0.05f},
          animMagic8{"rsrc/spritesheets/2_magic8_spritesheet.png", 100, 100, 0, 0, 61, 0.05f},
          animBlueFire{"rsrc/spritesheets/3_bluefire_spritesheet.png", 100, 100, 0, 0, 61, 0.05f},
          animCasting{ "rsrc/spritesheets/4_casting_spritesheet.png", 100, 100, 0, 0, 72, 0.05f },
          animMagicHit{"rsrc/spritesheets/5_magickahit_spritesheet.png", 100, 100, 0, 0, 42, 0.05f},
          animFlameLash{ "rsrc/spritesheets/6_flamelash_spritesheet.png", 100, 100, 0, 0, 46, 0.05f },
          animFireSpin{ "rsrc/spritesheets/7_firespin_spritesheet.png", 100, 100, 0, 0, 61, 0.05f},
          animProtectionCircle{ "rsrc/spritesheets/8_protectioncircle_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animBrightFire{ "rsrc/spritesheets/9_brightfire_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animWeaponHit{ "rsrc/spritesheets/10_weaponhit_spritesheet.png", 100, 100, 0, 0, 31, 0.05f },
          animFire{ "rsrc/spritesheets/11_fire_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animNebula{ "rsrc/spritesheets/12_nebula_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animVortex{ "rsrc/spritesheets/13_vortex_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animPhantom{"rsrc/spritesheets/14_phantom_spritesheet.png", 100, 100, 0, 0, 61, 0.05f},
          animLoading{ "rsrc/spritesheets/15_loading_spritesheet.png", 100, 100, 0, 0, 121, 0.05f },
          animSunburn{ "rsrc/spritesheets/16_sunburn_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animFelSpell{ "rsrc/spritesheets/17_felspell_spritesheet.png", 100, 100, 0, 0, 91, 0.05f },
          animMidknight{ "rsrc/spritesheets/18_midnight_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },
          animFreezing{ "rsrc/spritesheets/19_freezing_spritesheet.png", 100, 100, 0, 0, 86, 0.05f },
          animMagicBubble{ "rsrc/spritesheets/20_magicbubbles_spritesheet.png", 100, 100, 0, 0, 61, 0.05f },

          magicSpell{ sf::Vector2f{0, 0}, sf::Vector2f{2, 2} },
          magic8{ sf::Vector2f{200, 0}, sf::Vector2f{2, 2} },
          blueFire{ sf::Vector2f{400, 0}, sf::Vector2f{2, 2} },
          casting{ sf::Vector2f{600, 0}, sf::Vector2f{2, 2} },
          magicHit{ sf::Vector2f{800, 0}, sf::Vector2f{2, 2} },
          flameLash{ sf::Vector2f{1000, 0}, sf::Vector2f{2, 2} },
          fireSpin{ sf::Vector2f{1200, 0}, sf::Vector2f{2, 2} },
          protectionCircle{ sf::Vector2f{1400, 0}, sf::Vector2f{2, 2} },
          brightFire{ sf::Vector2f{1600, 0}, sf::Vector2f{2, 2} },
          weaponHit{ sf::Vector2f{1800, 0}, sf::Vector2f{2, 2} },
          fire{ sf::Vector2f{2000, 0}, sf::Vector2f{2, 2} },
          nebula{ sf::Vector2f{2200, 0}, sf::Vector2f{2, 2} },
          vortex{ sf::Vector2f{2400, 0}, sf::Vector2f{2, 2} },
          phantom{ sf::Vector2f{2600, 0}, sf::Vector2f{2, 2} },
          loading{ sf::Vector2f{2800, 0}, sf::Vector2f{2, 2} },
          sunburn{ sf::Vector2f{3000, 0}, sf::Vector2f{2, 2} },
          felSpell{ sf::Vector2f{0, 200}, sf::Vector2f{2, 2} },
          midknight{ sf::Vector2f{200, 200}, sf::Vector2f{2, 2} },
          freezing{ sf::Vector2f{400, 200}, sf::Vector2f{2, 2} },
          magicBubble{ sf::Vector2f{600, 200}, sf::Vector2f{2, 2} },

		ta{ magicSpell, sf::Vector2f{0, 0}, sf::Vector2f{1000, 1000}, 100 },
		ta2{ flameLash, sf::Vector2f{1000, 0}, sf::Vector2f{300, 1800}, 100 },
		ta3{ phantom, sf::Vector2f{2600, 0}, sf::Vector2f{100, 700}, 100 }
    {
        magicSpell.addAnimation(EAnimation::IDLE, &animMagicSpell);
        magic8.addAnimation(EAnimation::IDLE, &animMagic8);
        blueFire.addAnimation(EAnimation::IDLE, &animBlueFire);
        casting.addAnimation(EAnimation::IDLE, &animCasting);
        magicHit.addAnimation(EAnimation::IDLE, &animMagicHit);
        flameLash.addAnimation(EAnimation::IDLE, &animFlameLash);
        fireSpin.addAnimation(EAnimation::IDLE, &animFireSpin);
        protectionCircle.addAnimation(EAnimation::IDLE, &animProtectionCircle);
        brightFire.addAnimation(EAnimation::IDLE, &animBrightFire);
        weaponHit.addAnimation(EAnimation::IDLE, &animWeaponHit);
        fire.addAnimation(EAnimation::IDLE, &animFireSpin);
        nebula.addAnimation(EAnimation::IDLE, &animNebula);
        vortex.addAnimation(EAnimation::IDLE, &animVortex);
        phantom.addAnimation(EAnimation::IDLE, &animPhantom);
        loading.addAnimation(EAnimation::IDLE, &animLoading);
        sunburn.addAnimation(EAnimation::IDLE, &animSunburn);
        felSpell.addAnimation(EAnimation::IDLE, &animFelSpell);
        midknight.addAnimation(EAnimation::IDLE, &animMidknight);
        freezing.addAnimation(EAnimation::IDLE, &animFreezing);
        magicBubble.addAnimation(EAnimation::IDLE, &animMagicBubble);

        addEntities({ &magicSpell, &magic8, &blueFire, &casting, &magicHit, &flameLash, &fireSpin, &protectionCircle, &brightFire, 
        	&weaponHit, &fire, &nebula, &vortex, &phantom, &loading, &sunburn, &felSpell, &midknight, &freezing, &magicBubble,
			&ta, &ta2, &ta3});

        addDrawables({ &magicSpell, &magic8, &blueFire, &casting, &magicHit, &flameLash, &fireSpin, &protectionCircle, &brightFire, 
        	&weaponHit, &fire, &nebula, &vortex, &phantom, &loading, &sunburn, &felSpell, &midknight, &freezing, &magicBubble });

		ta.start();
		ta2.start();
		ta3.start();
    }

	void DebugScene::update(sf::Time time)
	{
		if (InputManager::getInstance().onKeyPressed(sf::Keyboard::Space))
		{
			if (ta.getTo() == sf::Vector2f{ 1000, 1000 })
			{
				ta.setTo(sf::Vector2f{ 0, 0 });
			}
			else
			{
				ta.setTo(sf::Vector2f{ 1000, 1000 });
			}

			if (ta2.getTo() == sf::Vector2f{ 300, 1800 })
			{
				ta2.setTo(sf::Vector2f{ 1000, 0 });
			}
			else
			{
				ta2.setTo(sf::Vector2f{ 300, 1800 });
			}

			if (ta3.getTo() == sf::Vector2f{100, 700})
			{
				ta3.setTo(sf::Vector2f{2600, 0});
			}
			else
			{
				ta3.setTo(sf::Vector2f{ 100, 700 });
			}

			ta.setFrom(ta.getTranslatable().getPosition());
			ta.start();

			ta2.setFrom(ta2.getTranslatable().getPosition());
			ta2.start();

			ta3.setFrom(ta3.getTranslatable().getPosition());
			ta3.start();
		}

		Scene::update(time);
	}
}