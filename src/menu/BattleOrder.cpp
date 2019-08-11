
#include "BattleOrder.h"

namespace ProjectSpace
{
	BattleOrder::BattleOrder(std::vector<Character*> characters, sf::Vector2f position, float spacing, float cycleDuration)
	: position{position}, spacing{spacing}, width{0}, height{0}
	{
			// Sort Characters by agility decending
		std::sort(characters.begin(), characters.end(), [](Character* c1, Character* c2)
		{
			return c1->getAgility() > c2->getAgility();
		});

			// Add sorted Characters to Queue so that Character with highest agility has firs turn in Battle.
		for (Character* c : characters)
		{
			this->characters.push(c);
		}

			// Add RectangleShapes and position them accordingly. Also add their TranslateAnimations.
		Portrait* firstPortrait = new Portrait{sf::Vector2f{50, 50}, position};
		firstPortrait->setFillColor(sf::Color{34, 139, 34, 255});
		portraits.push_back(firstPortrait);

		for (int i = 1; i < characters.size(); ++i)
		{
			Portrait* portrait = new Portrait{sf::Vector2f{50, 50}};
			sf::Vector2f portraitPos{position.x, portraits[i - 1]->getPosition().y + portraits[i - 1]->getHeight() + spacing};
			portrait->setPosition(portraitPos);
			portrait->setFillColor(sf::Color(32,178,170));
			portraits.push_back(portrait);

			anims.push_back(new TranslateAnimation{portrait, portraitPos, portraits[i - 1]->getPosition(), 1000});
		}
		anims.insert(anims.begin(), new TranslateAnimation{firstPortrait, firstPortrait->getPosition(), portraits[portraits.size() - 1]->getPosition(), 1000});

			// Calculate BattleOrder width and height.
		width = portraits[0]->getWidth();
		Portrait* p;

		for (int i = 0; i < portraits.size() - 1; ++i)
		{
			p = portraits[i];

			if (width < p->getWidth())
			{
				width = p->getWidth();
			}

			height += p->getHeight();
		}
		height += (portraits.size() - 1) * spacing;
	}

	BattleOrder::~BattleOrder()
	{
		for (int i = 0; i < portraits.size(); ++i)
		{
			delete portraits[i];
			delete anims[i];
		}
	}

	void BattleOrder::update(sf::Time time)
	{
		for (auto* ta : anims)
		{
			ta->update(time);
		}

			// Wait till the longest Animation is finished.
		if (anims[0]->isFinished())
		{
				// Gives the MenuElement of the current TransalteAnimation to the next TranslateAnimation.
			MenuElement* temp = anims[anims.size() - 1]->getMenuElement();
			for (int i = anims.size() - 2; i >= 0; --i)
			{
				anims[i + 1]->setMenuElement(anims[i]->getMenuElement());
			}
			anims[0]->setMenuElement(temp);

				// Reset all Animations so they can play again.
			for (TranslateAnimation* ta : anims)
			{
				ta->reset();
			}
		}
	}

	void BattleOrder::cycle()
	{
		for (TranslateAnimation* ta : anims)
		{
			ta->start();
		}
	}

	void BattleOrder::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (Portrait* portrait : portraits)
		{
			target.draw(*portrait);
		}
	}

	float BattleOrder::getWidth() const
	{
		return width;
	}

	float BattleOrder::getHeight() const
	{
		return height;
	}

	sf::Vector2f BattleOrder::getPosition() const
	{
		return position;
	}

	void BattleOrder::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;

		portraits[0]->setPosition(position);
		for (int i = 1; i < portraits.size(); ++i)
		{
			portraits[i]->setPosition(position.x, portraits[i - 1]->getPosition().y + portraits[i - 1]->getHeight() + spacing);
		}
	}

	void BattleOrder::setPosition(sf::Vector2f v)
	{
		position = v;

		portraits[0]->setPosition(position);
		for (int i = 1; i < portraits.size(); ++i)
		{
			portraits[i]->setPosition(position.x, portraits[i - 1]->getPosition().y + portraits[i - 1]->getHeight() + spacing);
		}
	}

	void BattleOrder::move(float x, float y)
	{
		position.x += x;
		position.y += y;

		for (Portrait* p : portraits)
		{
			p->move(x, y);
		}
	}

	void BattleOrder::move(sf::Vector2f v)
	{
		position += v;

		for (Portrait* p : portraits)
		{
			p->move(v);
		}
	}
}