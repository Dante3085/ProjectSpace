
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
		cycleTriggered{false}
	{
		std::vector<Character*> allChars{ party1 };
		for (Character*& c : party2)
			allChars.push_back(c);

		std::sort(allChars.begin(), allChars.end(), [](Character*& c1, Character*& c2) -> bool
			{
				return c1->getAgility() > c2->getAgility();
			});

		Portrait* firstPortrait = new Portrait{ position, portraitSize, portraitDefaultColor };
		portraits.push_back(firstPortrait);

		for (int i = 1; i < allChars.size(); ++i)
		{
			sf::Vector2f portraitPos{ position.x, portraits[i - 1]->getY() + portraits[i - 1]->getHeight() + spacing };
			Portrait* portrait = new Portrait{ portraitPos, portraitSize, portraitDefaultColor };
			portraits.push_back(portrait);

			TranslateAnimation ta{ *portrait, portrait->getPosition(), portraits[i - 1]->getPosition(), 6000 };
			ta.setEasingFunction(Easing::linear_easeNone);
			translateAnimations.push_back(ta);
		}
		TranslateAnimation taFirstPortrait{ *firstPortrait, firstPortrait->getPosition(), 
			portraits[portraits.size()-1]->getPosition(), 6000 };
		taFirstPortrait.setEasingFunction(Easing::linear_easeNone);
		translateAnimations.push_back(taFirstPortrait);

		Translatable* temp = &translateAnimations[0].getTranslatable();
		TranslateAnimation* ta = nullptr;
		for (int i = 0; i < translateAnimations.size() - 1; ++i)
		{
			ta = &translateAnimations[i];
			ta->setOnFinished([ta, this, i]()
				{
					ta->setTranslatable(translateAnimations[i + 1].getTranslatable());
				});
		}
		ta = &translateAnimations[translateAnimations.size() - 1];
		ta->setOnFinished([ta, temp]()
			{
				ta->setTranslatable(*temp);
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
		cycleTriggered = true;

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
		
	}

	void BattleOrder::setPosition(float x, float y) 
	{

	}

	void BattleOrder::move(sf::Vector2f const& by) 
	{

	}

	void BattleOrder::move(float byX, float byY) 
	{

	}

	sf::Vector2f BattleOrder::getPosition() const 
	{
		return portraits[0]->getPosition();
	}

	float BattleOrder::getX() const 
	{
		return portraits[0]->getX();
	}

	float BattleOrder::getY() const 
	{
		return portraits[0]->getY();
	}

	sf::Vector2f BattleOrder::getSize() const 
	{
		return portraitSize;
	}

	float BattleOrder::getWidth() const 
	{
		return portraitSize.x;
	}
	
	float BattleOrder::getHeight() const 
	{
		return portraitSize.y;
	}
}