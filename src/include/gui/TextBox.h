//
//#ifndef TEXTBOX_H
//#define TEXTBOX_H
//
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/Text.hpp>
//#include <SFML/Graphics/RenderTarget.hpp>
//#include <SFML/Graphics/RectangleShape.hpp>
//
//#include <iostream>
//#include <stdio.h>
//#include "MenuElement.h"
//
//namespace ProjectSpace
//{
//	/**
//	 * @brief      A TextBox for displaying Text in the Game.
//	 */
//	class TextBox : public MenuElement
//	{
//	public:
//
//		/**
//		 * @brief      Constructs the object.
//		 *
//		 * @param[in]  texturePath  The texture path
//		 * @param[in]  str          The string
//		 * @param[in]  width        The width
//		 * @param[in]  height       The height
//		 */
//		TextBox(std::string texturePath, sf::String str, sf::Vector2f size = sf::Vector2f{100, 100}, sf::Vector2f position = sf::Vector2f{0, 0});
//
//		/**
//		 * @brief      Draws Rectangle and Text of this TextBox(Draws this TextBox).
//		 *
//		 * @param      target  The target
//		 * @param[in]  states  The states
//		 */
//		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//
//		/**
//		 * @brief      { function_description }
//		 *
//		 * @param[in]  time  The time
//		 */
//		void update(sf::Time time) override;
//
//		void setOpacity(int opacity);
//		void setPadding(float padding);
//		
//		void setPosition(float x, float y) override;
//		void setPosition(sf::Vector2f const& position) override;
//		void move(float x, float y) override;
//		void move(sf::Vector2f v) override;
//		void setSize(float width, float height);
//		void setSize(sf::Vector2f const& size);
//		sf::Vector2f getPosition() const;
//		float getWidth() const override;
//		float getHeight() const override;
//
//	private:
//
//
//		/**
//		 * @brief      Checks if Text reaches over TextBox's edge taking padding into account and corrects for that.
//		 */
//		void parseText();
//
//		sf::String str;
//		sf::Text text;
//		sf::Font font;
//		sf::Texture texture;
//		sf::RectangleShape rec;
//		sf::Vector2f position;
//		float padding;
//	};
//}
//
//#endif