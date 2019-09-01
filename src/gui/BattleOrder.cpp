
#include "gui/BattleOrder.h"

namespace ProjectSpace
{
	BattleOrder::BattleOrder(std::vector<Character*> characters, sf::Vector2f const& position)
		: position{ position }, characters{ characters }, doUpdate{ false }
	{

		/*Portrait* p = new Portrait{};
		p->setPosition(position);
		tas.push_back(new TranslateAnimation{ p, position, position + sf::Vector2f{0, 100}, 1000 });
		for (int i = 1; i < characters.size(); ++i)
		{
			p = new Portrait{};
			p->setPosition(tas[i - 1]->getMenuElement()->getPosition() + sf::Vector2f{ 0, 100 });
			tas.push_back(new TranslateAnimation{ p, p->getPosition(), p->getPosition() + sf::Vector2f{0, 100}, 1000 });
		}*/
	}

	void BattleOrder::update(sf::Time time)
	{
		/*if (doUpdate)
		{
			for (TranslateAnimation* ta : tas)
			{
				ta->update(time);
			}
		}*/
	}

	void BattleOrder::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		/*for (TranslateAnimation* ta : tas)
		{
			target.draw(*ta->getMenuElement());
		}*/
	}

	void BattleOrder::cycle()
	{
		/*doUpdate = true;
		for (TranslateAnimation* ta : tas)
		{
			ta->start();
		}*/
	}
}