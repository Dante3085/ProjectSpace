
#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

#include "MenuElement.h"

namespace ProjectSpace
{
	/**
	 * @brief      For drawing the FPS on screen.
	 */
	class FpsCounter : public MenuElement
	{
	public:
		FpsCounter(std::string fontPath, int x = 0, int y = 0);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setPosition(sf::Vector2f const& position) override;
		void setPosition(float x, float y) override;
		void move(sf::Vector2f const& by) override;
		void move(float byX, float byY) override;
		sf::Vector2f getPosition() const override;
		float getX() const override;
		float getY() const override;
		sf::Vector2f getSize() const override;
		float getWidth() const;
		float getHeight() const;

		void setHide(bool hide);
		bool isHidden();

	private:
		sf::Font font; 	 	   // Font of FpsCounter text.
		sf::Text text; 	 	   // Displayable Text of the FpsCounter.
		std::string str; 	   // Text Content of the FpsCounter.
		sf::Vector2f position; // Position of the FpsCounter. OVERHEAD (Muss ueberall veraendert werden)

		bool hide;
	};
}

#endif