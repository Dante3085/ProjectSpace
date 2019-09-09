
#ifndef TRANSLATABLE_H
#define TRANSLATABLE_H

#include <SFML/System/Vector2.hpp>

class Translatable
{
public:
	virtual ~Translatable() {}

	virtual void setPosition(sf::Vector2f const& position) = 0;
	virtual void setPosition(float x, float y) = 0;

	virtual void move(sf::Vector2f const& by) = 0;
	virtual void move(float byX, float byY) = 0;

	virtual sf::Vector2f getPosition() const = 0;
	virtual float getX() const = 0;
	virtual float getY() const = 0;

	virtual sf::Vector2f getSize() const = 0;
	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;
};

#endif