
#include "gui/BattleOrder.h"

#include <algorithm>

#include "utility/Log.h"

namespace ProjectSpace
{
	BattleOrder::Portrait::Portrait(sf::Vector2f const& position, sf::Vector2f const& size, sf::Color const& color)
	{
		shape.setPosition(position);
		shape.setSize(size);
		shape.setFillColor(color);
	}

	BattleOrder::Portrait::Portrait(sf::Vector2f const& position, sf::Vector2f const& size, std::string const& texturePath)
	{
		shape.setPosition(position);
		shape.setSize(size);
		
		texture.loadFromFile(texturePath);
		shape.setTexture(&texture);
	}

	void BattleOrder::Portrait::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
	}

	void BattleOrder::Portrait::setPosition(sf::Vector2f const& position) 
	{
		shape.setPosition(position);
	}

	void BattleOrder::Portrait::setPosition(float x, float y) 
	{
		shape.setPosition(x, y);
	}

	void BattleOrder::Portrait::move(sf::Vector2f const& by) 
	{
		shape.move(by);
	}

	void BattleOrder::Portrait::move(float byX, float byY) 
	{
		shape.move(byX, byY);
	}

	sf::Vector2f BattleOrder::Portrait::getPosition() const 
	{
		return shape.getPosition();
	}

	float BattleOrder::Portrait::getX() const 
	{
		return shape.getPosition().x;
	}

	float BattleOrder::Portrait::getY() const 
	{
		return shape.getPosition().y;
	}

	sf::Vector2f BattleOrder::Portrait::getSize() const 
	{
		return shape.getSize();
	}

	float BattleOrder::Portrait::getWidth() const 
	{
		return shape.getSize().x;
	}

	float BattleOrder::Portrait::getHeight() const 
	{
		return shape.getSize().y;
	}

	BattleOrder::BattleOrder(std::vector<Character*> party1, std::vector<Character*> party2,
		std::vector<std::string> texturePaths, sf::Vector2f const& position)
		: portraitSize{ 200, 200 }, portraitDefaultColor{ sf::Color(135,206,235, 200) }, spacing{ 10 },
		cycleDuration{400}
	{
		if ((party1.size() + party2.size()) != texturePaths.size())
		{
			Log::getInstance().defaultLog("Number of Characters has to be number of texturePaths for now.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}

		std::vector<Character*> allChars{ party1 };
		for (Character*& c : party2)
			allChars.push_back(c);

		std::sort(allChars.begin(), allChars.end(), [](Character*& c1, Character*& c2) -> bool
			{
				return c1->getAgility() > c2->getAgility();
			});

		Portrait* firstPortrait = new Portrait{ position, portraitSize, texturePaths[0]};
		portraits.push_back(firstPortrait);

		for (int i = 1; i < allChars.size(); ++i)
		{
			sf::Vector2f portraitPos{ position.x, portraits[i - 1]->getY() + portraits[i - 1]->getHeight() + spacing };
			Portrait* portrait = new Portrait{ portraitPos, portraitSize, texturePaths[i] };
			portraits.push_back(portrait);

			TranslateAnimation ta{ *portrait, portrait->getPosition(), portraits[i - 1]->getPosition(), cycleDuration };
			ta.setEasingFunction(Easing::linear_easeNone);
			translateAnimations.push_back(ta);
		}

		// TranslateAnimation of the first Portrait has to be set last, because it translates
		// the first Portrait to the position of the last Portrait, which is available only 
		// after the previous loop.
		TranslateAnimation taFirstPortrait{ *firstPortrait, firstPortrait->getPosition(), 
			portraits[portraits.size()-1]->getPosition(), cycleDuration };
		taFirstPortrait.setEasingFunction(Easing::linear_easeNone);
		translateAnimations.push_back(taFirstPortrait);

		// Give all TranslateAnimations their next Translatable, which is the Portrait
		// that is below each TranslateAnimation's current Portrait. In case of the last
		// TranslateAnimation it is the Portrait at the top.
		// This process needs to happen after the last TranslateAnimation has finished to
		// ensure that every other TranslateAnimation has already finished.
		translateAnimations[translateAnimations.size() - 1].setOnFinished([this]()
			{
				Translatable* temp = &translateAnimations[0].getTranslatable();
				TranslateAnimation* ta = nullptr;

				for (int i = 0; i < translateAnimations.size(); ++i)
				{
					ta = &translateAnimations[i];
					if (i == translateAnimations.size() - 1)
					{
						ta->setTranslatable(*temp);
					}
					else
					{
						ta->setTranslatable(translateAnimations[i + 1].getTranslatable());
					}
				}
			});

		for (Character*& c : allChars)
			queue.push(c);
	}

	BattleOrder::~BattleOrder()
	{
		for (Portrait* p : portraits)
		{
			delete p;
		}
	}

	void BattleOrder::update(sf::Time time)
	{
		for (TranslateAnimation& t : translateAnimations)
		{
 			t.update(time);
		}
	}

	void BattleOrder::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (Portrait const* p : portraits)
		{
			target.draw(*p);
		}
	}

	// Switches to next turn(Moves every Character up one place in the queue).
	void BattleOrder::cycle()
	{
		Character* temp = queue.front();
		queue.pop();
		queue.push(temp);

		for (TranslateAnimation& t : translateAnimations)
		{
			t.start();
		}
	}

	// Returns Pointer to Character whose turn it is right now.
	Character* BattleOrder::getCurrentCharacter()
	{
		return queue.front();
	}

	void BattleOrder::setPosition(sf::Vector2f const& position) 
	{
		sf::Vector2f shiftVector = position - translateAnimations[0].getTranslatable().getPosition();
		move(shiftVector);
	}

	void BattleOrder::setPosition(float x, float y) 
	{
		sf::Vector2f currentPosition = translateAnimations[0].getTranslatable().getPosition();
		sf::Vector2f shiftVector = sf::Vector2f{ x - currentPosition.x, y - currentPosition.y };
		move(shiftVector);
	}

	void BattleOrder::move(sf::Vector2f const& by) 
	{
		Portrait* tempPo = nullptr;
		TranslateAnimation* tempTa = nullptr;
		for (int i = 0; i < portraits.size(); ++i)
		{
			tempPo = portraits[i];
			tempTa = &translateAnimations[i];

			tempPo->move(by);
			tempTa->setFrom(tempTa->getFrom() + by);
			tempTa->setTo(tempTa->getTo() + by);
		}
	}

	void BattleOrder::move(float byX, float byY) 
	{
		sf::Vector2f by{ byX, byY };

		Portrait* tempPo = nullptr;
		TranslateAnimation* tempTa = nullptr;
		for (int i = 0; i < portraits.size(); ++i)
		{
			tempPo = portraits[i];
			tempTa = &translateAnimations[i];

			tempPo->move(by);
			tempTa->setFrom(tempTa->getFrom() + by);
			tempTa->setTo(tempTa->getTo() + by);
		}
	}

	// Die Position der BattleOrder ist nicht die Position des 0ten Portraits
    // (Dessen Position ‰ndert sich ja), sondern die Position des obersten Portraits.
	// Das heiﬂt die Position des Portraits von translateAnimations[0].

	sf::Vector2f BattleOrder::getPosition() const 
	{
		return translateAnimations[0].getTranslatable().getPosition();
	}

	float BattleOrder::getX() const 
	{
		return translateAnimations[0].getTranslatable().getX();
	}

	float BattleOrder::getY() const 
	{
		return translateAnimations[0].getTranslatable().getY();
	}

	sf::Vector2f BattleOrder::getSize() const 
	{
		int numPortraits = portraits.size();
		float height = numPortraits * portraitSize.y + (numPortraits - 1) * spacing;

		return sf::Vector2f{ portraitSize.x, height };
	}

	float BattleOrder::getWidth() const 
	{
		return portraitSize.x;
	}
	
	float BattleOrder::getHeight() const 
	{
		return getSize().y;
	}
}