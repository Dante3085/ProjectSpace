
#ifndef EXPAND_MENU_H
#define EXPAND_MENU_H

#include <map>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "MenuElement.h"
#include "Button.h"
#include "ButtonMenu.h"
#include "VBox.h"
#include "HBox.h"
#include "TranslateAnimation.h"

namespace ProjectSpace
{
	class ExpandMenu : public MenuElement
	{
	public:
		ExpandMenu(std::map<Button*, std::vector<Button*>> const& buttons, 
			sf::Vector2f const& position, InputHandler* inputHandler);

		void update(sf::Time time) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		float getWidth() const override;
		float getHeight() const override;
		sf::Vector2f getPosition() const override;
		void setPosition(float x, float y) override;
		void setPosition(sf::Vector2f v) override;
		void move(float x, float y) override;
		void move(sf::Vector2f v) override;

	private:
		
	private:
		std::map<Button*, std::vector<Button*>> buttons;
		std::vector<ButtonMenu> buttonMenus;
		std::vector<VBox> vboxs;
		std::vector<TranslateAnimation> tForwardAnims;
		std::vector<TranslateAnimation> tBackwardAnims;
		sf::Vector2f position;
	};

	/*class ExpandMenu : public MenuElement
	{
	public:
		ExpandMenu();

	private:
		class Node
		{
		public:
			Node(std::vector<Button*> buttons);

			// Sets given Node to Button on the given index.
			// Does nothing if buttonIndex is invalid.
			void setNode(int buttonIndex, Node& node);

		private:
			std::map<Button*, Node> nodes;
			ButtonMenu buttonMenu;
			VBox vbox;
			TranslateAnimation translateAnimation;
		};

	private:
		Node root;
	};*/
}

#endif