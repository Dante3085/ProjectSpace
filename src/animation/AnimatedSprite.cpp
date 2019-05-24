
#include "AnimatedSprite.h"

#include <stdio.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Util.h"

namespace ProjectSpace
{
	AnimatedSprite::AnimatedSprite(sf::Vector2f position)
		: currentAnimation{ EAnimation::NONE }, frameIndex{ 0 }, elapsedSeconds{ 0 }, 
		  previousPosition{ sprite.getPosition() }, layerCollidable{position, sf::Vector2f{}}
	{
		sprite.setPosition(position);
		sprite.setTextureRect(sf::IntRect{ 0, 0, 100, 100 });
		sprite.setScale(2, 2);

		layerCollidable.setOulineThickness(2);
		layerCollidable.setOutlineColor(sf::Color{ 30,144,255 });
		layerCollidable.setFillColor(sf::Color{ 0, 0, 0, 0 });
		layerCollidable.setPosition(position);
	}

	void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);
		target.draw(layerCollidable);
	}

	void AnimatedSprite::update(sf::Time time)
	{
		playAnimation(time);
	}

	void AnimatedSprite::setAnimation(EAnimation name)
	{
		// Do nothing if Animation is already set.
		if (currentAnimation == name)
		{
			return;
		}

		// Do nothing if Animation is not known to this AnimatedSprite.
		else if (animations.count(name) == 0)
		{
			std::cout << "@AnimatedSprite::setAnimation(): Given Animation is not known to this AnimatedSprite." << std::endl;
			return;
		}

		currentAnimation = name;
		sprite.setTexture(animations[name]->getSpriteSheet());
		elapsedSeconds = 0;
		frameIndex = 0;
	}

	void AnimatedSprite::addAnimation(EAnimation name, Animation* animation)
	{
		animations[name] = animation;
	}

	void AnimatedSprite::playAnimation(sf::Time time)
	{
		Animation* currentAnim = animations[currentAnimation];

		if (elapsedSeconds >= currentAnim->getFrameDelay())
		{
			frameIndex = (frameIndex + 1) == currentAnim->size() ? 0 : ++frameIndex;
			sprite.setTextureRect((*currentAnim)[frameIndex]);
			elapsedSeconds = 0;
		}
		elapsedSeconds += time.asSeconds();
	}

	sf::Vector2f AnimatedSprite::getPreviousPosition() const
	{
		return previousPosition;
	}

	void AnimatedSprite::setPosition(float x, float y)
	{
		sprite.setPosition(x, y);
		layerCollidable.setPosition(sf::Vector2f{ x, y });
	}

	void AnimatedSprite::setPosition(sf::Vector2f const& position)
	{
		sprite.setPosition(position);
		layerCollidable.setPosition(position);
	}

	void AnimatedSprite::setRotation(float angle)
	{
		sprite.setRotation(angle);
	}

	void AnimatedSprite::setScale(float factorX, float factorY)
	{
		sprite.setScale(factorX, factorY);
	}

	void AnimatedSprite::setScale(const sf::Vector2f & factors)
	{
		sprite.setScale(factors);
	}

	void AnimatedSprite::setOrigin(float x, float y)
	{
		sprite.setOrigin(x, y);
	}

	void AnimatedSprite::setOrigin(const sf::Vector2f & origin)
	{
		sprite.setOrigin(origin);
	}

	const sf::Vector2f& AnimatedSprite::getPosition() const
	{
		return sprite.getPosition();
	}

	float AnimatedSprite::getRotation() const 						 
	{ 
		return sprite.getRotation(); 
	}

	const sf::Vector2f& AnimatedSprite::getScale() const 			 
	{ 
		return sprite.getScale(); 
	}

	const sf::Vector2f& AnimatedSprite::getOrigin() const 			 
	{ 
		return sprite.getOrigin(); 
	}

	void AnimatedSprite::move(float x, float y) 					 
	{
		previousPosition = sf::Vector2f{sprite.getPosition()};
		sprite.move(x, y); 
		layerCollidable.move(sf::Vector2f{x, y});
	}

	void AnimatedSprite::move(const sf::Vector2f& offset) 			 
	{ 
		previousPosition = sf::Vector2f{ sprite.getPosition() };
		sprite.move(offset); 
		layerCollidable.move(offset);
	}

	void AnimatedSprite::rotate(float angle) 						 
	{ 
		sprite.rotate(angle); 
	}

	void AnimatedSprite::scale(float factorX, float factorY) 		 
	{ 
		sprite.scale(factorX, factorY); 
	}

	void AnimatedSprite::scale(const sf::Vector2f& factor) 			 
	{ 
		sprite.scale(factor); 
	}

	const sf::Transform& AnimatedSprite::getTransform() const 		 
	{ 
		return sprite.getTransform(); 
	}

	const sf::Transform& AnimatedSprite::getInverseTransform() const 
	{ 
		return sprite.getInverseTransform(); 
	}

	sf::Sprite* AnimatedSprite::getSprite()
	{
		return &sprite;
	}

	LayerCollidable* AnimatedSprite::getLayerCollidable()
	{
		return &layerCollidable;
	}
}