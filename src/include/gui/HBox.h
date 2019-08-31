
#ifndef HBOX_H
#define HBOX_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>

#include "MenuElement.h"

namespace ProjectSpace
{
    class HBox : public MenuElement
    {
    public:
        HBox(float spacing = 0);
        HBox(std::vector<MenuElement *> menuElements, sf::Vector2f position, float spacing = 0);

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
        void addMenuElement(MenuElement *m);
        void addMenuElements(std::vector<MenuElement *> menuElements);
        void setSpacing(float spacing);

    private:
        void updatePositions();
        void updateWidth();
        void updateHeight();

    private:
        sf::FloatRect bounds;
        std::vector<MenuElement *> menuElements;
        float spacing;
        bool hidden;
    };
}

#endif