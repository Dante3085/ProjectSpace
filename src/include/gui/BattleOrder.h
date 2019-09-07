
#ifndef BATTLE_ORDER_H
#define BATTLE_ORDER_H

#include <queue>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <string>

#include "gui/MenuElement.h"
#include "rpg/Character.h"
#include "animation/TranslateAnimation.h"
#include "animation/Translatable.h"

namespace ProjectSpace
{
	class BattleOrder : public MenuElement
	{
	public:
		BattleOrder(std::vector<Character*> party1, std::vector<Character*> party2, 
			std::vector<std::string> texturePaths, sf::Vector2f const& = sf::Vector2f{0, 0});
		~BattleOrder();

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		// Switches to next turn(Moves every Character up one place in the queue).
		void cycle();

		// Returns Pointer to Character whose turn it is right now.
		Character* getCurrentCharacter();

		void setPosition(sf::Vector2f const& position) override;
		void setPosition(float x, float y) override;
		void move(sf::Vector2f const& by) override;
		void move(float byX, float byY) override;
		sf::Vector2f getPosition() const override;
		float getX() const override;
		float getY() const override;
		sf::Vector2f getSize() const override;
		float getWidth() const override;
		float getHeight() const override;

	private:

		class Portrait : public Translatable, public sf::Drawable
		{
		public:
			Portrait(sf::Vector2f const& position, sf::Vector2f const& size, sf::Color const& color);
			Portrait(sf::Vector2f const& position, sf::Vector2f const& size, std::string const& texturePath);

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			void setPosition(sf::Vector2f const& position) override;
			void setPosition(float x, float y) override;
			void move(sf::Vector2f const& by) override;
			void move(float byX, float byY) override;
			sf::Vector2f getPosition() const override;
			float getX() const override;
			float getY() const override;
			sf::Vector2f getSize() const override;
			float getWidth() const override;
			float getHeight() const override;

		private:
			sf::RectangleShape shape;
			sf::Texture texture;
		};

	private:
		std::queue<Character*> queue;
		std::vector<Portrait*> portraits;
		std::vector<sf::Texture> textures;
		std::vector<TranslateAnimation> translateAnimations;

		sf::Vector2f portraitSize;
		sf::Color portraitDefaultColor;
		float spacing;
		float cycleDuration;
	};
}

#endif