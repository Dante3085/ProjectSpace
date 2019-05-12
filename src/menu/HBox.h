
#ifndef HBOX_H
#define HBOX_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>

#include "../game/Entity.h"
#include "../menu/MenuElement.h"

namespace ProjectSpace
{
	class HBox : public MenuElement
	{
	public:
		HBox(float spacing = 0);
		HBox(std::vector<MenuElement*> menuElements, sf::Vector2f position, float spacing = 0);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void show();
		void hide();
		bool isHidden();
		void setNeedsUpdate();
		void addMenuElement(MenuElement* b);
		void addMenuElements(std::vector<MenuElement*> menuElements);
		void setSpacing(float spacing);
		void setPosition(float x, float y) override;
		void setPosition(sf::Vector2f v) override;
		void move(float x, float y) override;
		void move(sf::Vector2f v) override;
		float getWidth() const override;
		float getHeight() const override;
		sf::Vector2f getPosition() const;

	private:
		sf::Vector2f position;
		std::vector<MenuElement*> menuElements;
		float spacing;
		bool needsUpdate;
		bool hidden;
	};
}

#endif