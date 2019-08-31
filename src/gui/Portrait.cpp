//
//#include "Portrait.h"
//
//namespace ProjectSpace
//{
//	Portrait::Portrait(sf::Vector2f size, sf::Vector2f position, std::string texturePath)
//	: shape{size}
//	{
//		shape.setPosition(position);
//
//		if (texturePath != "NONE")
//		{
//			texture.loadFromFile(texturePath);
//			shape.setTexture(&texture);
//		}
//		else
//		{
//			shape.setFillColor(sf::Color(135,206,235, 200));
//		}
//	}
//
//	void Portrait::update(sf::Time time)
//	{
//			// TODO(moritz):
//	}
//
//	void Portrait::draw(sf::RenderTarget& target, sf::RenderStates states) const
//	{
//		target.draw(shape);
//	}
//
//	float Portrait::getWidth() const
//	{
//		return shape.getGlobalBounds().width;
//	}
//
//	float Portrait::getHeight() const
//	{
//		return shape.getGlobalBounds().height;
//	}
//
//	sf::Vector2f Portrait::getPosition() const
//	{
//		return sf::Vector2f{shape.getGlobalBounds().left, shape.getGlobalBounds().top};
//	}
//
//	void Portrait::setPosition(float x, float y)
//	{
//		shape.setPosition(x, y);
//	}
//
//	void Portrait::setPosition(sf::Vector2f const& position)
//	{
//		shape.setPosition(position);
//	}
//
//	void Portrait::move(float x, float y)
//	{
//		shape.move(x, y);
//	}
//
//	void Portrait::move(sf::Vector2f v)
//	{
//		shape.move(v);
//	}
//
//	void Portrait::setFillColor(sf::Color color)
//	{
//		shape.setFillColor(color);
//	}
//}