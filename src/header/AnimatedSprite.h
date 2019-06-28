
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
#include "Collidable.h"
#include "EAnimation.h"
#include "Animation.h"
#include "CollisionShape.h"
#include "LayerCollidable.h"

namespace ProjectSpace
{
	class AnimatedSprite : public sf::Drawable, public Entity
	{
	public:

		/**
		 * @brief      Uses Rectangle for CollisionDetection.
		 *
		 * @param[in]  position      Initial position of the AnimatedSprite
		 * @param[in]  speed  Pixels per Second that this AnimatedSprite moves (NICHT IMPLEMENTIERT)
		 */
		AnimatedSprite(sf::Vector2f position, std::vector<sf::Vector2f> const& points = {});

		/**
		 * @brief      Draws this AnimatedSprite on given RenderTarget. Makes following Syntax possible: RenderTarget.draw(AnimatedSprite)
		 *
		 * @param      target  The RenderTarget (Usually sf::RenderWindow)
		 * @param[in]  states  The states (No idea what that is ;D)
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief      Updates this AnimatedSprite every frame.
		 *
		 * @param[in]  time  Time that passed since last update call.
		 */
		void update(sf::Time time) override;

		/**
		 * @brief      Sets the animation.
		 *
		 * @param[in]  name  The name of the Animation that the caller wants to set.
		 */
		void setAnimation(EAnimation name);

		/**
		 * @brief      Adds an animation.
		 *
		 * @param[in]  name       Identifies the given Animation object.
		 * @param      animation  New Animation.
		 */
		void addAnimation(EAnimation name, Animation* animation);

		sf::Vector2f getPreviousPosition() const;
		float getSpeed();
		void setSpeed(float speed);
		void setPosition(float x, float y);
		void setPosition(sf::Vector2f const& position);
		void setRotation(float angle);
		void setScale(float factorX, float factorY);
		void setScale(const sf::Vector2f& factors);
		void setOrigin(float x, float y);
		void setOrigin(const sf::Vector2f& origin);
		const sf::Vector2f& getPosition() const;
		float getRotation() const;
		const sf::Vector2f& getScale() const;
		const sf::Vector2f& getOrigin() const;
		void move(float x, float y);
		void move(const sf::Vector2f& offset);
		void rotate(float angle);
		void scale(float factorX, float factorY);
		void scale(const sf::Vector2f& factor);
		const sf::Transform& getTransform() const;
		const sf::Transform& getInverseTransform() const;

		sf::Sprite* getSprite();
		LayerCollidable* getLayerCollidable();

	private:
		/**
		 * @brief      Plays the current Animation of this AnimatedSprite. Updates the current Animation's frames.
		 *
		 * @param[in]  time  Time given by update method. So, time since last update call.
		 */
		void playAnimation(sf::Time time);

		sf::Sprite sprite; 							 // Displays a frame of this AnimatedSprite at any given moment in time.
		std::map<EAnimation, Animation*> animations; // Contains all Animations registered on this AnimatedSprite by name.
		EAnimation currentAnimation; 				 // Name of the current Animation of this AnimatedSprite.
		int frameIndex; 							 // Stores on which frame of the current Animation the AnimatedSprite is currently on.
		float elapsedSeconds; 						 // For tracking time when updating frames.
		float speed; 								 // Pixels per Second.
		sf::Vector2f previousPosition;

		LayerCollidable layerCollidable;
	};
}

#endif