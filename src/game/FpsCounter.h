
#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>

#include "../menu/MenuElement.h"

namespace ProjectSpace
{
	/**
	 * @brief      For drawing the FPS on screen.
	 */
	class FpsCounter : public MenuElement
	{
	public:

		/**
		 * @brief      Constructs the FPSCounter with the given Font at the given Position.
		 *
		 * @param[in]  fontPath  The font path.
		 * @param[in]  x         X-Coordinate
		 * @param[in]  y         Y-Coordinate
		 */
		FpsCounter(std::string fontPath, int x = 0, int y = 0);

		/**
		 * @brief      Updates the displayed Text of the FPSCounter each Frame.
		 *
		 * @param[in]  time  The time
		 */
		void update(sf::Time time) override;

		/**
		 * @brief      For drawing the FpsCounter to the screen.
		 *
		 * @param      target  The target
		 * @param[in]  states  The states
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief      Gets the position of the FpsCounter.
		 *
		 * @return     The position.
		 */
		sf::Vector2f getPosition() const;

		/**
		 * @brief      Gets the width of the FpsCounter.
		 *
		 * @return     The width.
		 */
		float getWidth() const;

		/**
		 * @brief      Gets the height of the FpsCounter.
		 *
		 * @return     The height.
		 */
		float getHeight() const;

		/**
		 * @brief      Sets the position.
		 *
		 * @param[in]  x     { parameter_description }
		 * @param[in]  y     { parameter_description }
		 */
		void setPosition(float x, float y);

		/**
		 * @brief      Sets the position of the FpsCounter.
		 *
		 * @param[in]  v     { parameter_description }
		 */
		void setPosition(sf::Vector2f v);
		void move(float x, float y);
		void move(sf::Vector2f v);

	private:
		sf::Font font; 	 	   // Font of FpsCounter text.
		sf::Text text; 	 	   // Displayable Text of the FpsCounter.
		std::string str; 	   // Text Content of the FpsCounter.
		sf::Vector2f position; // Position of the FpsCounter. OVERHEAD (Muss ueberall veraendert werden)
	};
}

#endif