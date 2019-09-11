
#include "gui/List.h"

#include <SFML/Window/Mouse.hpp>

#include "utility/Log.h"
#include "utility/Util.h"

namespace ProjectSpace
{
	// I am not doing bounds{position.x, position.y, -1, -1} because topText will be set to position
	// and sf::Text::getPosition() will not return the upperLeft corner of visible sf::Text, only
	// sf::Text::getGlobalBounds() will.

	List::List(sf::Vector2f const& position, sf::Window const& window, 
		std::vector<std::pair<std::string, std::function<void()>>> const& strings)
		: bounds{-1, -1, -1, -1}, spacing{ 10 }, visibleItems{ 5 }, top{ 0 }, bottom{ visibleItems - 1 }, current{ 0 },
		pressKey{ sf::Keyboard::Enter }, pressKeyPreviouslyPressed{ false }, upPreviouslyPressed{false},
		downPreviouslyPressed{ false }, leftMousePreviouslyPressed{false}, window{ window }
	{

		// Don't allow empty List for now
		// TODO: Make empty list and append possible.
		if (strings.size() == 0)
		{
			Log::getInstance().defaultLog("Give at least one string and callback.", ll::ERR);
			Log::getInstance() << lo::EXIT;
		}

		// There can not be more ListItems visible than actually exist.
		if (visibleItems > strings.size())
		{
			visibleItems = strings.size();
			bottom = visibleItems - 1;
		}

		font.loadFromFile("rsrc/fonts/joystix_monospace.ttf");

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

		// Init List bounds
		// Can only be done after all Texts have been positioned correctly.
		sf::FloatRect* currentTextBounds = &texts[0].first.getGlobalBounds();
		bounds.left = currentTextBounds->left;
		bounds.top = currentTextBounds->top;

		float width = currentTextBounds->width;
		float height = currentTextBounds->height;

		for (int i = 1; i < texts.size(); ++i)
		{
			currentTextBounds = &texts[i].first.getGlobalBounds();

			if (width < currentTextBounds->width)
			{
				width = currentTextBounds->width;
			}
			height += currentTextBounds->height;
		}
		height += (texts.size() - 1) * spacing;

		bounds.width = width;
		bounds.height = height;

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
		if ((!pressKeyPreviouslyPressed & (pressKeyPreviouslyPressed = sf::Keyboard::isKeyPressed(pressKey))))
		{
			texts[current].second();
		}

		// Check if one of the visible ListItems is selected by Mouse.
		// Only check for all ListItems if Mouse is already inside
		// the List's bounds to avoid unnecessary checks.
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
		if (bounds.contains(mousePosition))
		{
			for (int i = top; i <= bottom; ++i)
			{
				sf::FloatRect textBounds = texts[i].first.getGlobalBounds();

				if (textBounds.contains(mousePosition))
				{
					current = i;
					selector.setPosition(textBounds.left, textBounds.top);
					selector.setSize(sf::Vector2f{ textBounds.width, textBounds.height });
					break;
				}
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
		// Draw all visible ListItems and selector.
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
		sf::Vector2f shiftVector = position - sf::Vector2f{ bounds.left, bounds.top };
		move(shiftVector);
	}

	void List::setPosition(float x, float y)
	{
		sf::Vector2f shiftVector = sf::Vector2f{ x - bounds.left, y - bounds.top };
		move(shiftVector);
	}

	void List::move(sf::Vector2f const& by)
	{
		for (auto& pair : texts)
		{
			pair.first.move(by);
		}
		bounds.left += by.x;
		bounds.top += by.y;
	}

	void List::move(float byX, float byY)
	{
		for (auto& pair : texts)
		{
			pair.first.move(byX, byY);
		}
		bounds.left += byX;
		bounds.top += byY;
	}

	sf::Vector2f List::getPosition() const
	{
		return sf::Vector2f{ bounds.left, bounds.top };
	}

	float List::getX() const
	{
		return bounds.left;
	}

	float List::getY() const
	{
		return bounds.top;
	}

	sf::Vector2f List::getSize() const
	{
		return sf::Vector2f{ bounds.width, bounds.height };
	}

	float List::getWidth() const
	{
		return bounds.width;
	}

	float List::getHeight() const
	{
		return bounds.height;
	}

	sf::FloatRect List::getBounds() const
	{
		return bounds;
	}
}