
#include "gui/List.h"

#include <cmath>

#include "utility/Log.h"
#include "utility/Util.h"

namespace ProjectSpace
{
	int List::numLists = 0;

	// TODO: Mit mittlerem MouseButton durch die Liste scrollen.
	// TODO: Localizer soll auch auf Selektion mit Maus reagieren.

	// I am not doing bounds{position.x, position.y, -1, -1} because topText will be set to position
	// and sf::Text::getPosition() will not return the upperLeft corner of visible sf::Text, only
	// sf::Text::getGlobalBounds() will.

	List::List(sf::Vector2f const& position, std::vector<std::pair<std::string, std::function<void()>>> const& strings)
		: bounds{ -1, -1, -1, -1 },
		hoverColor{ 105,105,105 },
		nonHoverColor{ sf::Color::White },
		topArrow{ 3 },
		mouseHoversTopArrow{ false },
		bottomArrow{ 3 },
		mouseHoversBottomArrow{ false },
		localizerSpacing{ 5 },
		localizerYFirstSegment{ -1 },
		localizerYLastSegment{ -1 },
		localizerSegmentHeight{ -1 },
		localizerTotalVerticalSpace{ -1 },
		mouseHoversLocalizer{ false },
		localizerTopOrBottomColor{255, 88, 88},
		textSpacing{ 10 },
		visibleItems{ 10 },
		top{ 0 },
		bottom{ visibleItems - 1 },
		current{ 0 },
		upHoldDuration{ 500 },
		upHoldElapsed{ 0 },
		downHoldDuration{ 500 },
		downHoldElapsed{ 0 },
		inputManager{ &InputManager::getInstance() },
		inputContext{ "include/input/contexts/ListContext.txt" },
		mouseInsideBounds{false}
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
										  sf::Vector2f{0, texts[i - 1].first.getGlobalBounds().height + textSpacing} };
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

		for (int i = 1; i < visibleItems; ++i)
		{
			currentTextBounds = &texts[i].first.getGlobalBounds();

			if (width < currentTextBounds->width)
			{
				width = currentTextBounds->width;
			}
			height += currentTextBounds->height;
		}
		height += (visibleItems - 1) * textSpacing;

		bounds.width = width;
		bounds.height = height;

		// Init selector rectangle.
		sf::FloatRect topTextBounds = texts[0].first.getGlobalBounds();
		selector.setPosition(topTextBounds.left, topTextBounds.top);
		selector.setSize(sf::Vector2f{ topTextBounds.width, topTextBounds.height });
		selector.setFillColor(sf::Color::Red);

		// Init Arrows.
		float textHeight = texts[0].first.getGlobalBounds().height;
		topArrow.setPoint(0, sf::Vector2f{ bounds.left - 40, bounds.top + textHeight });
		topArrow.setPoint(1, sf::Vector2f{ bounds.left - 10, bounds.top + textHeight });
		topArrow.setPoint(2, sf::Vector2f(bounds.left - 25, bounds.top));

		bottomArrow.setPoint(0, sf::Vector2f{ bounds.left - 40, bounds.top + bounds.height - textHeight });
		bottomArrow.setPoint(1, sf::Vector2f{ bounds.left - 10, bounds.top + bounds.height - textHeight });
		bottomArrow.setPoint(2, sf::Vector2f(bounds.left - 25, bounds.top + bounds.height));

		// Expand bounds to include arrows.
		sf::FloatRect tempBounds = bounds;
		bounds.left = topArrow.getPoint(0).x;
		bounds.width = (tempBounds.left + tempBounds.width) - bounds.left;

		// Init localizer. Should already be inside bounds. No extra calculations needed.
		localizerYFirstSegment = topArrow.getPoint(0).y + localizerSpacing;
		localizerTotalVerticalSpace = (bottomArrow.getPoint(0).y - localizerSpacing) -
			(localizerYFirstSegment);
		localizerSegmentHeight = localizerTotalVerticalSpace / strings.size();
		localizerYLastSegment = bottomArrow.getPoint(0).y - localizerSpacing - localizerSegmentHeight;

		float localizerWidth = (topArrow.getPoint(1).x - localizerSpacing) - (topArrow.getPoint(0).x + localizerSpacing);
		localizer.setSize(sf::Vector2f{ localizerWidth, localizerSegmentHeight });
		localizer.setPosition(topArrow.getPoint(0).x + localizerSpacing, localizerYFirstSegment);
		localizer.setFillColor(hoverColor);

		// Setup Input with InputManager.
		inputContext.setPredicate([this]()
			{
				// TODO: Wie kann man einfach den Fokus auf einen InputContext setzen, sodass die Maus nicht immer in den
				// bounds sein muss.
				// return bounds.contains((sf::Vector2f)sf::Mouse::getPosition(this->window));
				return true;
			});
		std::string inputContextName = "gui/List";
		inputContextName += std::to_string(numLists++);
		inputManager->registerInputContext(inputContextName, &inputContext);
	}

	void List::update(sf::Time time)
	{
		// TODO: Check this function for improvements in performance.

		if (inputContext.isValid())
		{
			// Check if current ListItem is pressed.
			if (inputContext.hasActionFired(Action::LIST_SELECT))
			{
				texts[current].second();
			}

			if (inputContext.hasActionFired(Action::LIST_UP))
			{
				up();
			}

			if (inputContext.isStateOn(State::LIST_HOLD_UP))
			{
				if (upHoldElapsed >= upHoldDuration)
				{
					up();
					upHoldElapsed *= 0.90f;
				}
				else
				{
					upHoldElapsed += time.asMilliseconds();
				}
			}
			else
			{
				upHoldElapsed = 0;
			}

			if (inputContext.hasActionFired(Action::LIST_DOWN))
			{
				down();
			}

			if (inputContext.isStateOn(State::LIST_HOLD_DOWN))
			{
				if (downHoldElapsed >= downHoldDuration)
				{
					down();
					downHoldElapsed *= 0.90;
				}
				else
				{
					downHoldElapsed += time.asMilliseconds();
				}
			}
			else
			{
				downHoldElapsed = 0;
			}

			if (inputManager->hasMouseMoved())
			{
				sf::Vector2f mousePosition = (sf::Vector2f)inputManager->getMousePosition();

				if (bounds.contains(mousePosition))
				{
					mouseInsideBounds = true;

					if (topArrow.getGlobalBounds().contains(mousePosition))
					{
						mouseHoversTopArrow = true;
						mouseHoversBottomArrow = false;
						mouseHoversLocalizer = false;

						topArrow.setFillColor(hoverColor);
					}
					else if (bottomArrow.getGlobalBounds().contains(mousePosition))
					{
						mouseHoversTopArrow = false;
						mouseHoversBottomArrow = true;
						mouseHoversLocalizer = false;

						bottomArrow.setFillColor(hoverColor);
					}
					else if (localizer.getGlobalBounds().contains(mousePosition))
					{
						mouseHoversTopArrow = false;
						mouseHoversBottomArrow = false;
						mouseHoversLocalizer = true;

						localizer.setFillColor(hoverColor);
					}
					else
					{
						mouseHoversTopArrow = false;
						mouseHoversBottomArrow = false;
						mouseHoversLocalizer = false;

						topArrow.setFillColor(nonHoverColor);
						bottomArrow.setFillColor(nonHoverColor);
						localizer.setFillColor(current == 0 || current == texts.size() - 1 ?
							localizerTopOrBottomColor : nonHoverColor);

						for (int i = top; i <= bottom; ++i)
						{
							sf::FloatRect textBounds = texts[i].first.getGlobalBounds();

							if (textBounds.contains(mousePosition))
							{
								current = i;
								selector.setPosition(textBounds.left, textBounds.top);
								selector.setSize(sf::Vector2f{ textBounds.width, textBounds.height });

								localizer.setPosition(localizer.getPosition().x,
									localizerYFirstSegment + (current * localizerSegmentHeight));

								localizer.setFillColor(current == 0 || current == texts.size() - 1 ?
									localizerTopOrBottomColor : nonHoverColor);

								break;
							}
						}
					}
				}
				else
				{
					// TODO: Solution that detects the Mouse leaving Bounds. Doing this all the time is bad.
					// Also try that for above code.

					mouseInsideBounds = false;

					mouseHoversTopArrow = false;
					mouseHoversBottomArrow = false;
					mouseHoversLocalizer = false;

					topArrow.setFillColor(nonHoverColor);
					bottomArrow.setFillColor(nonHoverColor);
					localizer.setFillColor(current == 0 || current == texts.size() - 1 ?
						localizerTopOrBottomColor : nonHoverColor);
				}
			}

			if (mouseInsideBounds)
			{
				float mouseWheelDelta = inputManager->getMouseWheelDelta();
				float absMouseWheelDelta = abs(mouseWheelDelta);

				// Check if mouse wheel was moved enough to count as a single scroll
				// This is mainly to avoid accidental scrolling on high precision laptop tochpads.
				if (absMouseWheelDelta >= 0.01)
				{
					if (mouseWheelDelta < 0)
					{
						for (int i = 0; i < absMouseWheelDelta; ++i)
						{
							down();
						}
					}
					else if (mouseWheelDelta > 0)
					{
						for (int i = 0; i < absMouseWheelDelta; ++i)
						{
							up();
						}
					}
				}
			}

			if (mouseHoversTopArrow)
			{
				if (inputManager->onMouseButtonPressed(sf::Mouse::Button::Left))
				{
					up();
				}
			}
			else if (mouseHoversBottomArrow)
			{
				if (inputManager->onMouseButtonPressed(sf::Mouse::Button::Left))
				{
					down();
				}
			}
			else if (mouseHoversLocalizer)
			{
				if (inputManager->onMouseButtonPressed(sf::Mouse::Button::Left))
				{
					std::cout << "Selector clicked\n";
				}
			}
		}
	}

	void List::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(selector);
		target.draw(localizer);
		// Draw all visible ListItems and selector.
		for (int i = top; i <= bottom; ++i)
		{
			target.draw(texts[i].first);
		}
		target.draw(topArrow);
		target.draw(bottomArrow);
	}

	void List::up()
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

		// Set Localizer Position to represent current ListItem
		// and if necessary fill it with a special color when
		// it is on the last or first ListItem.
		localizer.setPosition(localizer.getPosition().x,
			localizerYFirstSegment + (current * localizerSegmentHeight));

		localizer.setFillColor(current == 0 || current == texts.size() - 1 ?
			localizerTopOrBottomColor : nonHoverColor);

		// ATTENTION: sf::Text::getPosition() does not return the same position as
		// sf::Text::getGlobalBounds()'s left and top.
		sf::FloatRect currentTextBounds = texts[current].first.getGlobalBounds();
		selector.setPosition(currentTextBounds.left, currentTextBounds.top);
		selector.setSize(sf::Vector2f{ currentTextBounds.width, currentTextBounds.height });
	}

	void List::down()
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

		// Set Localizer Position to represent current ListItem
		// and if necessary fill it with a special color when
		// it is on the last or first ListItem.
		localizer.setPosition(localizer.getPosition().x,
			localizerYFirstSegment + (current * localizerSegmentHeight));

		localizer.setFillColor(current == 0 || current == texts.size() - 1 ?
			                   localizerTopOrBottomColor : nonHoverColor);

		// ATTENTION: sf::Text::getPosition() does not return the same position as
		// sf::Text::getGlobalBounds()'s left and top.
		sf::FloatRect currentTextBounds = texts[current].first.getGlobalBounds();
		selector.setPosition(currentTextBounds.left, currentTextBounds.top);
		selector.setSize(sf::Vector2f{ currentTextBounds.width, currentTextBounds.height });
	}

	// TODO: Alle Positionierungsfunktionen updatet, da neue Elemente hinzugekommen sind.

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

		selector.move(by);
		topArrow.move(by);
		bottomArrow.move(by);
	}

	void List::move(float byX, float byY)
	{
		for (auto& pair : texts)
		{
			pair.first.move(byX, byY);
		}
		bounds.left += byX;
		bounds.top += byY;

		selector.move(byX, byY);
		topArrow.move(byX, byY);
		bottomArrow.move(byX, byY);
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

	void List::setColor(sf::Color const& color)
	{
		for (auto& pair : texts)
		{
			pair.first.setFillColor(color);
		}
		topArrow.setFillColor(color);
		bottomArrow.setFillColor(color);
		selector.setFillColor(sf::Color(255, 0, 0, color.a));
	}

	sf::FloatRect List::getBounds() const
	{
		return bounds;
	}

	void List::updateLocalizer()
	{
		localizer.setPosition(localizer.getPosition().x,
			localizerYFirstSegment + (current * localizerSegmentHeight));

		if (current == 0 || current == texts.size() - 1)
		{
			localizer.setFillColor(localizerTopOrBottomColor);
		}
		else if (mouseHoversLocalizer)
		{
			localizer.setFillColor(hoverColor);
		}
		else
		{
			localizer.setFillColor(nonHoverColor);
		}
	}
}