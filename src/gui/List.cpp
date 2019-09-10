
#include "gui/List.h"

#include <SFML/Window/Mouse.hpp>

#include "utility/Log.h"
#include "utility/Util.h"

namespace ProjectSpace
{
	List::List(sf::Vector2f const& position, sf::Window const& window, 
		std::vector<std::pair<std::string, std::function<void()>>> const& strings)
		: position{position}, spacing{ 10 }, visibleItems{ 4 }, top{ 0 }, bottom{ visibleItems - 1 }, current{ 0 },
		pressKey{ sf::Keyboard::Enter }, pressKeyPreviouslyPressed{ false }, upPreviouslyPressed{false},
		downPreviouslyPressed{false}, window{window}
	{
		if (visibleItems > strings.size())
		{
			visibleItems = strings.size();
			bottom = visibleItems - 1;
		}

		font.loadFromFile("rsrc/fonts/joystix_monospace.ttf");

		if (strings.size() == 0)
		{
			Log::getInstance().defaultLog("Give at least one string and callback.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}

		// Position all sf::Texts in vertical sequence.
		for (int i = 0; i < strings.size(); ++i)
		{
			sf::Text text{ strings[i].first, font };
			if (i == 0)
			{
				text.setPosition(position);
			}
			else
			{
				sf::Vector2f newPosition{ texts[i - 1].first.getPosition() +
									      sf::Vector2f{0, texts[i - 1].first.getGlobalBounds().height + spacing} };
				text.setPosition(newPosition);
			}
			texts.push_back(std::pair<sf::Text, std::function<void()>> {text, strings[i].second});
		}

		// Init selector rectangle.
		sf::FloatRect topTextBounds = texts[0].first.getGlobalBounds();
		selector.setPosition(topTextBounds.left, topTextBounds.top);
		selector.setSize(sf::Vector2f{ topTextBounds.width, topTextBounds.height });
		selector.setFillColor(sf::Color{255, 0, 0, 50});
	}

	void List::update(sf::Time time)
	{
		// TODO: Check this function for improvements in performance.
		// TODO: InputHandling needs work. New Input System.

		// Check if current ListItem is pressed.
		if (!pressKeyPreviouslyPressed & (pressKeyPreviouslyPressed = sf::Keyboard::isKeyPressed(pressKey)))
		{
			texts[current].second();
		}

		// Check if one of the visible ListItems is selected by Mouse.
		for (int i = top; i <= bottom; ++i)
		{
			sf::FloatRect textBounds = texts[i].first.getGlobalBounds();

			if (textBounds.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
			{
				current = i;
				selector.setPosition(textBounds.left, textBounds.top);
				selector.setSize(sf::Vector2f{ textBounds.width, textBounds.height });
				break;
			}
		}

		// Check if we need to move one ListItem up.
		if (!upPreviouslyPressed &(upPreviouslyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
		{
			// Vom Anfang zum Ende der Liste.
			if (current == 0)
			{
				// Remember previous positions
				std::vector<sf::Vector2f> prevPositions;
				for (int i = top; i <= bottom; ++i)
				{
					prevPositions.push_back(texts[i].first.getPosition());
				}

				int lastListItem = texts.size() - 1;

				current = lastListItem;
				bottom = lastListItem;
				top = current - (visibleItems - 1); // -1, da das aktuell auch mitzählt.

				// Reposition Texts.
				int posCounter = 0;
				for (int i = top; i <= bottom; ++i)
				{
					texts[i].first.setPosition(prevPositions[posCounter++]);
				}
			}

			// Über das oberste sichtbare ListItem hinweg.
			else if (current == top)
			{
				--current;
				--top;
				--bottom;

				// Reposition Texts.
				for (int i = top; i <= bottom; ++i)
				{
					texts[i].first.setPosition(texts[i + 1].first.getPosition());
				}
			}

			// Sonst einfach einen nach oben.
			else
			{
				--current;
			}

			// ATTENTION: sf::Text::getPosition() does not return the same position as
			// sf::Text::getGlobalBounds()'s left and top.
			sf::FloatRect currentTextBounds = texts[current].first.getGlobalBounds();
			selector.setPosition(currentTextBounds.left, currentTextBounds.top);
			selector.setSize(sf::Vector2f{ currentTextBounds.width, currentTextBounds.height });
		}

		// Check if we need to move one ListItem down.
		if (!downPreviouslyPressed & (downPreviouslyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)))
		{
			if (current == texts.size() - 1)
			{
				// Remember previous positions
				std::vector<sf::Vector2f> prevPositions;
				for (int i = top; i <= bottom; ++i)
				{
					prevPositions.push_back(texts[i].first.getPosition());
				}

				current = 0;
				top = 0;
				bottom = visibleItems - 1;

				// Reposition Texts.
				int posCounter = 0;
				for (int i = top; i <= bottom; ++i)
				{
					texts[i].first.setPosition(prevPositions[posCounter++]);
				}
			}
			else if (current == bottom)
			{
				++current;
				++bottom;
				++top;

				for (int i = bottom; i >= top; --i)
				{
					texts[i].first.setPosition(texts[i - 1].first.getPosition());
				}
			}
			else
			{
				++current;
			}
			// ATTENTION: sf::Text::getPosition() does not return the same position as
			// sf::Text::getGlobalBounds()'s left and top.
			sf::FloatRect currentTextBounds = texts[current].first.getGlobalBounds();
			selector.setPosition(currentTextBounds.left, currentTextBounds.top);
			selector.setSize(sf::Vector2f{ currentTextBounds.width, currentTextBounds.height });
		}
	}

	void List::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// Draw all visible ListItems.
		for (int i = top; i <= bottom; ++i)
		{
			target.draw(texts[i].first);
		}
		target.draw(selector);
	}

	sf::Text const& List::getTopText() const
	{
		return texts[0].first;
	}

	void List::setPosition(sf::Vector2f const& position)
	{
		sf::Vector2f shiftVector = position - texts[0].first.getPosition();
		move(shiftVector);
	}

	void List::setPosition(float x, float y)
	{
		sf::Vector2f currentPosition = texts[0].first.getPosition();
		sf::Vector2f shiftVector = sf::Vector2f{ x - currentPosition.x, y - currentPosition.y };
		move(shiftVector);
	}

	void List::move(sf::Vector2f const& by)
	{
		for (auto& pair : texts)
		{
			pair.first.move(by);
		}
	}

	void List::move(float byX, float byY)
	{
		for (auto& pair : texts)
		{
			pair.first.move(byX, byY);
		}
	}

	sf::Vector2f List::getPosition() const
	{
		return texts[0].first.getPosition();
	}

	float List::getX() const
	{
		return texts[0].first.getPosition().x;
	}

	float List::getY() const
	{
		return texts[0].first.getPosition().y;
	}

	sf::Vector2f List::getSize() const
	{
		float width = texts[0].first.getGlobalBounds().width;
		float tempWidth = 0;
		for (int i = 1; i < texts.size(); ++i)
		{
			tempWidth = texts[i].first.getGlobalBounds().width;
			if (tempWidth > width)
			{
				width = tempWidth;
			}
		}

		float height = 0;
		for (auto& pair : texts)
		{
			height += pair.first.getGlobalBounds().height;
		}

		return sf::Vector2f{ width, height };
	}

	float List::getWidth() const
	{
		return getSize().x;
	}

	float List::getHeight() const
	{
		return getSize().y;
	}
}