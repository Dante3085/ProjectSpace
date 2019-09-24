
#include "gui/Button.h"

namespace ProjectSpace
{
	// TODO: Initializing a Button takes long (~9-20ms). Loading Font. getGlobalBounds() takes long if sf::Text or 
	// sf::RectangleShape needs to run internal updates before returing the bounds.

	// TODO: Parse given string with Util function to properly insert new lines.

	Button::Button(std::function<void()> onPressed, sf::Window const& window, std::string const& string)
		: onPressed{onPressed}, 
		window{window}, 
		mouseOnButton{false},
		previousMouseOnButton{false}, 
	    leftMouseDown{false}, 
		previousLeftMouseDown{false}, 
		onSelected{[](){}}, 
		onUnselected{[](){}}, 
		str{string}
	{
		font.loadFromFile("rsrc/fonts/joystix_monospace.ttf");
		text.setFont(font);
		text.setString(string);

		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setFillColor(sf::Color(135,206,235, 200));
		setSize(200, 100);
		rectangle.setPosition(0, 0);

		onSelected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 255));
		};

		onUnselected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 200));
		};
	}

	Button::Button(sf::Window const& window, std::string const& string)
		: onPressed{[](){}}, 
		window{window}, 
		mouseOnButton{false}, 
		previousMouseOnButton{false}, 
	    leftMouseDown{false}, 
		previousLeftMouseDown{false}, 
		onSelected{[](){}}, 
		onUnselected{[](){}}, 
		str{string}
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
		};

		onUnselected = [this]()
		{
			this->setFillColor(sf::Color(135,206,235, 200));
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

	void Button::setPosition(sf::Vector2f const& position)
	{
		sf::Vector2f recSize = rectangle.getSize();
		sf::FloatRect textBounds = text.getGlobalBounds();

		text.setPosition(position.x + 0.5f * recSize.x - 0.5f * textBounds.width,
			             position.y + 0.5f * recSize.y - 0.5f * textBounds.height);

		rectangle.setPosition(position);
	}

	void Button::setPosition(float x, float y)
	{
		sf::Vector2f recSize = rectangle.getSize();
		sf::FloatRect textBounds = text.getGlobalBounds();

		text.setPosition(x + 0.5f * recSize.x - 0.5f * textBounds.width,
			             y + 0.5f * recSize.y - 0.5f * textBounds.height);

		rectangle.setPosition(x, y);
	}

	void Button::move(sf::Vector2f const& by)
	{
		rectangle.move(by);
		text.move(by);
	}

	void Button::move(float byX, float byY)
	{
		rectangle.move(byX, byY);
		text.move(byX, byY);
	}

	sf::Vector2f Button::getPosition() const
	{
		return rectangle.getPosition();
	}

	float Button::getX() const
	{
		return rectangle.getPosition().x;
	}

	float Button::getY() const
	{
		return rectangle.getPosition().y;
	}

	sf::Vector2f Button::getSize() const
	{
		return rectangle.getSize();
	}

	float Button::getWidth() const
	{
		return rectangle.getGlobalBounds().width;
	}

	float Button::getHeight() const
	{
		return rectangle.getGlobalBounds().height;
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

	void Button::setSize(float width, float height)
	{
		sf::Vector2f position = rectangle.getPosition();
		sf::FloatRect textBounds = text.getGlobalBounds();

		text.setPosition(position.x + 0.5f * width - 0.5f * textBounds.width,
			             position.y + 0.5f * height - 0.5f * textBounds.height);

		rectangle.setSize(sf::Vector2f(width, height));
	}

	void Button::setSize(sf::Vector2f const& size)
	{
		sf::Vector2f position = rectangle.getPosition();
		sf::FloatRect textBounds = text.getGlobalBounds();

		text.setPosition(position.x + 0.5f * size.x - 0.5f * textBounds.width,
			position.y + 0.5f * size.y - 0.5f * textBounds.height);

		rectangle.setSize(size);
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