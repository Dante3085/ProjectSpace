
#ifndef HBOX_H
#define HBOX_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>

#include "Entity.h"
#include "MenuElement.h"

namespace ProjectSpace
{
	class HBox : public MenuElement
	{
	public:
		HBox(float spacing = 0);
		HBox(std::vector<MenuElement*> menuElements, sf::Vector2f position, float spacing = 0);

		void update(sf::Time time) override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        
        void setPosition(sf::Vector2f const &position) override;
        void setPosition(float x, float y) override;
        void move(sf::Vector2f const &by) override;
        void move(float byX, float byY) override;
        sf::Vector2f getPosition() const override;
        float getX() const override;
        float getY() const override;
        sf::Vector2f getSize() const override;
        float getWidth() const override;
        float getHeight() const override;

        void show();
        void hide();
        bool isHidden();
        void setNeedsUpdate();
        void addMenuElement(MenuElement *m);
        void addMenuElements(std::vector<MenuElement *> menuElements);
        void setSpacing(float spacing);

	private:
		sf::Vector2f position;
		std::vector<MenuElement*> menuElements;
		float spacing;
		bool needsUpdate;
		bool hidden;
	};
}

#endif