
#include "Button.h"

namespace ProjectSpace
{
	Button::Button(std::function<void()> onPressed, sf::Window const& window, std::string string)
	: onPressed{onPressed}, window{window}, mouseOnButton{false}, previousMouseOnButton{false}, 
	leftMouseDown{false}, previousLeftMouseDown{false}, onSelected{[](){}}, onUnselected{[](){}}, str{string}
	{
		font.loadFromFile("rsrc/fonts/arial.ttf");
		text.setFont(font);
		text.setString(string);

		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setFillColor(sf::Color(135,206,235, 200));
		setSize(200, 100);
		rectangle.setPosition(0, 0);

		onSelected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 255));
			// this->move(5, 0);
		};

		onUnselected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 200));
			// this->move(-5, 0);
		};
	}

	Button::Button(sf::Window const& window, std::string string)
	: onPressed{[](){}}, window{window}, mouseOnButton{false}, previousMouseOnButton{false}, 
	leftMouseDown{false}, previousLeftMouseDown{false}, onSelected{[](){}}, onUnselected{[](){}}, str{string}
	{
		font.loadFromFile("rsrc/fonts/arial.ttf");
		text.setFont(font);
		text.setString(string);

		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setFillColor(sf::Color(135,206,235, 200));
		setSize(200, 100);
		rectangle.setPosition(0, 0);

		onSelected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 255));
			// this->move(5, 0);
		};

		onUnselected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 200));
			// this->move(-5, 0);
		};
	}

	void Button::update(sf::Time time)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		mouseOnButton = rectangle.getGlobalBounds().contains(mouse.x, mouse.y);
		leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

		if (!previousMouseOnButton && mouseOnButton)
		{
			onSelected();
		}

		if (!mouseOnButton && previousMouseOnButton)
		{
			onUnselected();
		}

		if (mouseOnButton && previousLeftMouseDown && !leftMouseDown)
		{
			onPressed();
		}

		previousLeftMouseDown = leftMouseDown;
		previousMouseOnButton = mouseOnButton;
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rectangle);
		target.draw(text);
	}

	void Button::setOnPressed(std::function<void()> onPressed)
	{
		this->onPressed = onPressed;
	}

	void Button::setOnSelected(std::function<void()> onSelected)
	{
		this->onSelected = onSelected;
	}

	void Button::setOnUnselected(std::function<void()> onUnselected)
	{
		this->onUnselected = onUnselected;
	}

	void Button::setFillColor(sf::Color color)
	{
		rectangle.setFillColor(color);
	}

	void Button::setOpacity(int opacity)
	{
		sf::Color c = rectangle.getFillColor();
		c.a = opacity;

		rectangle.setFillColor(c);
		text.setFillColor(c);
	}

	void Button::setPosition(float x, float y)
	{
		rectangle.setPosition(x, y);

		float textX = rectangle.getGlobalBounds().left + ((rectangle.getGlobalBounds().width / 2.f) - (text.getGlobalBounds().width / 2.f));
		float textY = rectangle.getGlobalBounds().top + (rectangle.getGlobalBounds().height / 2.f) - (text.getGlobalBounds().height / 2.f);
		text.setPosition(textX, textY);
	}

	void Button::setPosition(sf::Vector2f v)
	{
		rectangle.setPosition(v);

		float textX = rectangle.getGlobalBounds().left + ((rectangle.getGlobalBounds().width / 2.f) - (text.getGlobalBounds().width / 2.f));
		float textY = rectangle.getGlobalBounds().top + (rectangle.getGlobalBounds().height / 2.f) - (text.getGlobalBounds().height / 2.f);
		text.setPosition(textX, textY);
	}

	void Button::move(float x, float y)
	{
		rectangle.move(x, y);
		text.move(x, y);
	}

	void Button::move(sf::Vector2f v)
	{
		rectangle.move(v);
		text.move(v);
	}

	void Button::setSize(float width, float height)
	{
		rectangle.setSize(sf::Vector2f(width, height));

		float textX = rectangle.getGlobalBounds().left + ((rectangle.getGlobalBounds().width / 2.f) - (text.getGlobalBounds().width / 2.f));
		float textY = rectangle.getGlobalBounds().top + (rectangle.getGlobalBounds().height / 2.f) - (text.getGlobalBounds().height / 2.f);
		text.setPosition(textX, textY);
	}

	sf::Vector2f Button::getPosition() const
	{
		return rectangle.getPosition();
	}

	float Button::getWidth() const
	{
		return rectangle.getGlobalBounds().width;
	}

	float Button::getHeight() const
	{
		return rectangle.getGlobalBounds().height;
	}

	void Button::select() const
	{
		onSelected();
	}

	void Button::unselect() const
	{
		onUnselected();
	}

	void Button::press() const
	{
		onPressed();
	}
}