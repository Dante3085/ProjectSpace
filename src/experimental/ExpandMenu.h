
#ifndef EXPAND_MENU_H
#define EXPAND_MENU_H

namespace ProjectSpace
{
	class ExpandMenu
	{
	public:
		ExpandMenu() : root{nullptr} {}

		/**
		 * @brief     Fügt übergebenen Button in root Node ein.
		 */
		void addButton();
		void appendButton();

	private:
		Node* root;
		std::vector<std::string> btnNames; // Um schnell feststellen zu können, ob ein übergebener Buttonname im ExpandMenu schon existiert.
	};

	class Node
	{
	public:

		/**
		 * @brief      Fügt übergebenen Button in diese Node ein.
		 */
		void addButton(Button* btn);

		/**
		 * @brief      Fügt übergebenen Button in eine neue Node ein, die ein Nachfahre(nicht zwingend direkter Nachfahre) dieser Node wird.
		 */
		void appendButton();

	private:
		std::map<std::string, std::map<Button*, Node*>> btns; // Jeder Button in einer Node hat einen einzigartigen Namen und mapt auf weitere Nodes.
		VBox btnBox; 						 // Ordnet Buttons untereinander an.
		ButtonMenu btnMenu;  				 // Macht es möglich Buttons mit Pfeiltasten auszuwählen.
		TranslateAnimation tt; 				 // Macht es möglich Buttons zu animieren.
	};
}