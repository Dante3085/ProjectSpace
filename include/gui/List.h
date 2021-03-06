
#ifndef LIST_H
#define LIST_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <utility>
#include <string>
#include <functional>

#include "gui/MenuElement.h"
#include "animation/Fadeable.h"
#include "input/InputManager.h"

namespace ProjectSpace
{
	// GUI List Widget
	class List : public MenuElement, public Fadeable
	{

	public:
		List(sf::Vector2f const& position, std::vector<std::pair<std::string, std::function<void()>>> const& strings);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		// Select the ListItem directly above the current ListItem.
		void up();

		// Select the ListItem directly beneath the current ListItem.
		void down();

		// Translatable overrides
		void setPosition(sf::Vector2f const& position) override;
		void setPosition(float x, float y) override;
		void move(sf::Vector2f const& by) override;
		void move(float byX, float byY) override;
		sf::Vector2f getPosition() const override;
		float getX() const override;
		float getY() const override;
		sf::Vector2f getSize() const override;
		float getWidth() const override;
		float getHeight() const override;

		// Fadeable overrides
		void setColor(sf::Color const& color) override;

		sf::FloatRect getBounds() const;

		// Helper
	private:
		void checkInputActionsAndStates(sf::Time time);
		void checkMouseInteraction(sf::Time time);

	private:
		sf::FloatRect bounds;
		std::vector<std::pair<sf::Text, std::function<void()>>> texts;
		sf::Font font;               // Font of every Text.
		sf::Color hoverColor;
		sf::Color nonHoverColor;

		sf::ConvexShape topArrow;     // Click to go one ListItem up.
		bool mouseHoversTopArrow;

		sf::ConvexShape bottomArrow;  // Click to go one ListItem down.
		bool mouseHoversBottomArrow;

		sf::RectangleShape selector;  // Visually labels the current ListItem.

		sf::RectangleShape localizer; // Visual representation of the location of the selected ListItem relative to the whole List.
		float localizerSpacing;       // Space between localizer and all 4 adjacent sides.
		float localizerYFirstSegment; // Y-coordinate of the first Localizer segment.
		float localizerYLastSegment;  // Y-coordinate of the last Localizer segment.
		float localizerSegmentHeight; // Height of a Localizer segment.
		float localizerTotalVerticalSpace;
		bool mouseHoversLocalizer;
		sf::Color localizerTopOrBottomColor; // Color the Localizer has when on the first or last ListItem.

		float textSpacing;      	 // Vertical spacing between each Text.
		int visibleItems;   	     // Number of ListItems visible at the same time.
		int top;            	     // Index of first ListItem.
		int bottom;         	     // Index of last ListItem.
		int current;         	     // Index of currently selected ListItem.

		float upHoldDuration; // Amount of time that has to pass since the down key has been pressed and held down 
		                      // for it to be considered as a hold.
		float upHoldElapsed;  // Amount of time that has been passed since the down key has been pressed and held down.

		float downHoldDuration; // See: upHoldDuration
		float downHoldElapsed;  // See: upHoldElapsed

		InputManager* inputManager;
		InputContext inputContext;
		static int numLists;  // Mainly for having unique InputContext names for all List instances.

		bool mouseInsideBounds;
	};
}

#endif
