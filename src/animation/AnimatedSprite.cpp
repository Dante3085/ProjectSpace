
#include "animation/AnimatedSprite.h"

#include "utility/Util.h"
#include "utility/Log.h"

namespace ProjectSpace
{
    AnimatedSprite::AnimatedSprite(sf::Vector2f position, sf::Vector2f scale)
        : currentAnimation{ EAnimation::NONE }, 
		frameIndex{ 0 }, 
		elapsedSeconds{ 0 }, 
		speed{0}
    {
        sprite.setPosition(position);
		sprite.setScale(scale);
    }

    void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }

    void AnimatedSprite::update(sf::Time time)
    {
        playAnimation(time);
    }

    void AnimatedSprite::setPosition(sf::Vector2f const &position) 
    {
    	sprite.setPosition(position);
    }

    void AnimatedSprite::setPosition(float x, float y) 
    {
    	sprite.setPosition(x, y);
    }
    void AnimatedSprite::move(sf::Vector2f const &by) 
    {
    	sprite.move(by);
    }
    void AnimatedSprite::move(float byX, float byY) 
    {
    	sprite.move(byX, byY);
    }

    sf::Vector2f AnimatedSprite::getPosition() const 
    {
    	return sprite.getPosition();
    }

    float AnimatedSprite::getX() const 
    {
    	return sprite.getPosition().x;
    }

    float AnimatedSprite::getY() const 
    {
    	return sprite.getPosition().y;
    }

    sf::Vector2f AnimatedSprite::getSize() const 
    {
    	sf::FloatRect bounds = sprite.getGlobalBounds();
    	return sf::Vector2f{bounds.width, bounds.height};
    }

    float AnimatedSprite::getWidth() const 
    {
    	return sprite.getGlobalBounds().width;
    }

    float AnimatedSprite::getHeight() const 
    {
    	return sprite.getGlobalBounds().height;
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
            Log::getInstance() << lo::PTC << ll::ERR << "Given Animation is not known to this AnimatedSprite."
                               << lo::STACKTRACE << lo::END;
            return;
        }

        currentAnimation = name;
        sprite.setTexture(animations[currentAnimation]->getSpriteSheet());
        sprite.setTextureRect((*animations[currentAnimation])[0]);
        elapsedSeconds = 0;
        frameIndex = 0;

		std::cout << "setAnimation" << std::endl;
    }

    void AnimatedSprite::addAnimation(EAnimation name, Animation *animation)
    {
        animations[name] = animation;
		setAnimation(name);
    }

    void AnimatedSprite::setColor(sf::Color const &color)
    {
        sprite.setColor(color);
    }

    void AnimatedSprite::playAnimation(sf::Time time)
    {
        Animation *currentAnim = animations[currentAnimation];

        if (elapsedSeconds >= currentAnim->getFrameDelay())
        {
            frameIndex = (frameIndex + 1) == currentAnim->size() ? 0 : ++frameIndex;
            sprite.setTextureRect((*currentAnim)[frameIndex]);
            elapsedSeconds = 0;
        }
        elapsedSeconds += time.asSeconds();
    }

    void AnimatedSprite::setRotation(float angle)
    {
        sprite.setRotation(angle);
    }

    void AnimatedSprite::setScale(float factorX, float factorY)
    {
        sprite.setScale(factorX, factorY);
    }

    void AnimatedSprite::setScale(const sf::Vector2f &factors)
    {
        sprite.setScale(factors);
    }

    void AnimatedSprite::setOrigin(float x, float y)
    {
        sprite.setOrigin(x, y);
    }

    void AnimatedSprite::setOrigin(const sf::Vector2f &origin)
    {
        sprite.setOrigin(origin);
    }

    float AnimatedSprite::getRotation() const
    {
        return sprite.getRotation();
    }

    const sf::Vector2f &AnimatedSprite::getScale() const
    {
        return sprite.getScale();
    }

    const sf::Vector2f &AnimatedSprite::getOrigin() const
    {
        return sprite.getOrigin();
    }

    void AnimatedSprite::rotate(float angle)
    {
        sprite.rotate(angle);
    }

    void AnimatedSprite::scale(float factorX, float factorY)
    {
        sprite.scale(factorX, factorY);
    }

    void AnimatedSprite::scale(const sf::Vector2f &factor)
    {
        sprite.scale(factor);
    }

    const sf::Transform &AnimatedSprite::getTransform() const
    {
        return sprite.getTransform();
    }

    const sf::Transform &AnimatedSprite::getInverseTransform() const
    {
        return sprite.getInverseTransform();
    }
}