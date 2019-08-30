
#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <iostream>
#include <functional>
#include <vector>

#include "Entity.h"
#include "Fadeable.h"
#include "Collidable.h"
#include "Translatable.h"
#include "EAnimation.h"
#include "Animation.h"

namespace ProjectSpace
{
    class AnimatedSprite : public sf::Drawable, public Entity, public Fadeable, public Translatable
    {
    public:

        AnimatedSprite(sf::Vector2f position);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void update(sf::Time time) override;

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

        void setAnimation(EAnimation name);
        void addAnimation(EAnimation name, Animation *animation);
        void setColor(sf::Color const &color) override;
        void setRotation(float angle);
        void setScale(float factorX, float factorY);
        void setScale(const sf::Vector2f &factors);
        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f &origin);
        float getRotation() const;
        const sf::Vector2f &getScale() const;
        const sf::Vector2f &getOrigin() const;
        void rotate(float angle);
        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f &factor);
        const sf::Transform &getTransform() const;
        const sf::Transform &getInverseTransform() const;

    private:
        /**
         * @brief      Plays the current Animation of this AnimatedSprite. Updates the current Animation's frames.
         *
         * @param[in]  time  Time given by update method. So, time since last update call.
         */
        void playAnimation(sf::Time time);

        sf::Sprite sprite; 							 // Displays a frame of this AnimatedSprite at any given moment in time.
        std::map<EAnimation, Animation *> animations; // Contains all Animations registered on this AnimatedSprite by name.
        EAnimation currentAnimation; 				 // Name of the current Animation of this AnimatedSprite.
        int frameIndex; 							 // Stores on which frame of the current Animation the AnimatedSprite is currently on.
        float elapsedSeconds; 						 // For tracking time when updating frames.
        float speed; 								 // Pixels per Second.
    };
}

#endif