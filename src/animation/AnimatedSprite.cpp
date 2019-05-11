
#include "AnimatedSprite.h"

#include <stdio.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Util.h"

namespace ProjectSpace
{
	AnimatedSprite::AnimatedSprite(sf::Vector2f position)
		: currentAnimation{ EAnimation::NONE }, frameIndex{ 0 }, elapsedSeconds{ 0 }, 
		  previousPosition{ sprite.getPosition() }
	{
		sprite.setPosition(position);
		sprite.setTextureRect(sf::IntRect{ 0, 0, 100, 100 });
		sprite.setScale(2, 2);

		shape.setOutlineThickness(2);
		shape.setOutlineColor(sf::Color{ 30,144,255 });
		shape.setFillColor(sf::Color{ 0, 0, 0, 0 });

		// Lines of SpriteBox
		sf::FloatRect rect = sprite.getGlobalBounds();

		sf::Vector2f upperLeft = sf::Vector2f{ rect.left, rect.top };
		sf::Vector2f upperRight{ upperLeft.x + rect.width, upperLeft.y };
		sf::Vector2f lowerRight{ upperRight.x, upperLeft.y + rect.height };
		sf::Vector2f lowerLeft{ upperLeft.x, lowerRight.y };

		lines.push_back(new Line2F{ upperLeft, upperRight });
		lines.push_back(new Line2F{ upperRight, lowerRight });
		lines.push_back(new Line2F{ lowerRight, lowerLeft });
		lines.push_back(new Line2F{ lowerLeft, upperLeft });
	}

	void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);

		if (drawBoundingBox)
		{
			target.draw(shape);
		}
	}

	void AnimatedSprite::update(sf::Time time)
	{
		// update RectangleShape that describes the Sprite's bounds.
		sf::FloatRect rect = sprite.getGlobalBounds();
		shape.setSize(sf::Vector2f{ rect.width, rect.height });
		shape.setPosition(rect.left, rect.top);

		sf::Vector2f upperLeft = sf::Vector2f{ rect.left, rect.top };
		sf::Vector2f upperRight{ upperLeft.x + rect.width, upperLeft.y };
		sf::Vector2f lowerRight{ upperRight.x, upperLeft.y + rect.height };
		sf::Vector2f lowerLeft{ upperLeft.x, lowerRight.y };

		lines[0]->create(upperLeft, upperRight);
		lines[1]->create(upperRight, lowerRight);
		lines[2]->create(lowerRight, lowerLeft);
		lines[3]->create(lowerLeft, upperLeft);

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

	bool AnimatedSprite::collidesWith(Collidable const* partner) const
	{
		// return sprite.getGlobalBounds().intersects(partner->getGlobalBounds());
		return false;
	}

	sf::FloatRect AnimatedSprite::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

	sf::Shape const& AnimatedSprite::getShape() const
	{
		return shape;
	}

	sf::Vector2f AnimatedSprite::getPreviousPosition() const
	{
		return previousPosition;
	}

	void AnimatedSprite::setPosition(float x, float y)
	{
		sprite.setPosition(x, y);
	}

	void AnimatedSprite::setPosition(sf::Vector2f const& position)
	{
		sprite.setPosition(position);
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
	}

	void AnimatedSprite::move(const sf::Vector2f& offset) 			 
	{ 
		previousPosition = sf::Vector2f{ sprite.getPosition() };
		sprite.move(offset); 
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
}