
#ifndef VBOX_H
#define VBOX_H

#include <vector>
#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../game/Entity.h"
#include "../menu/MenuElement.h"

namespace ProjectSpace
{
	class VBox : public MenuElement
	{
	public:
		VBox();
		VBox(std::vector<MenuElement*> menuElements, sf::Vector2f position, float spacing = 0);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void show();
		void hide();
		void setNeedsUpdate();
		void addMenuElement(MenuElement* b);
		void addMenuElements(std::vector<MenuElement*> menuElements);
		void setPosition(float x, float y) override;
		void setPosition(sf::Vector2f v) override;
		void move(float x, float y) override;
		void move(sf::Vector2f v) override;
		void setSpacing(float spacing);
		float getWidth() const override;
		float getHeight() const override;
		sf::Vector2f getPosition() const;

	private:
		/*float x;
		float y;*/
		sf::Vector2f position;
		std::vector<MenuElement*> menuElements;
		float spacing;
		bool needsUpdate;
		bool hidden;
	};
}

#endif