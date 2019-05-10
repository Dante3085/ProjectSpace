
#ifndef TRANSLATE_ANIMATION
#define TRANSLATE_ANIMATION

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../game/Entity.h"
#include "../menu/Button.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for smoothly translating MenuElements from one point in 2D-Space to another.
	 */
	class TranslateAnimation : public Entity
	{
	public:

		/**
		 * @brief      Constructs a TranslateAnimation that can translate the given MenuElement from 'from' to 'to' 
		 * in the given duration.
		 *
		 * @param      menuElement  The menu element
		 * @param[in]  from         The point in 2D-Space the TranslateAnimation will start from.
		 * @param[in]  to           The point in 2D-Space the TranslateAnimation will end on.
		 * @param[in]  duration     The amount of time the TranslateAnimation will take to translate the Menuelement
		 * from 'from' to 'to'.
		 */
		TranslateAnimation(MenuElement* menuElement, sf::Vector2f from, sf::Vector2f to, float duration);

		/**
		 * @brief      Updates the TranslateAnimation each frame.
		 *
		 * @param[in]  time  The time that has passed since last update call.
		 */
		void update(sf::Time time) override;

		/**
		 * @brief      Sets the TranslateAnimation to update when update() is called.
		 */
		void start();

		/**
		 * @brief      Sets the TranslateAnimation to NOT update when update() is called.
		 */
		void pause();

		/**
		 * @brief      Resets the Translate Animation to it's initial State, so that it can play again.
		 * @problem    Not sure if this function should set the MenuElement to from. This function is subject to change.
		 */
		void reset();

		/**
		 * @brief      Gets the point in 2D-Space the TranslateAnimation will start from.
		 *
		 * @return     Point in 2D-Space the TranslateAnimation will start from.
		 */
		sf::Vector2f getFrom() const;

		/**
		 * @brief      Sets the point in 2D-Space the TranslateAnimation will start from.
		 *
		 * @param[in]  from Point in 2D-Space the TranslateAnimation will start from.
		 */
		void setFrom(sf::Vector2f from);

		/**
		 * @brief      Gets the point in 2D-Space the TranslateAnimation will end on.
		 *
		 * @return     Point in 2D-Space the TranslateAnimation will end on.
		 */
		sf::Vector2f getTo() const;

		/**
		 * @brief      Sets the point in 2D-Space the TranslateAnimation will end on.
		 *
		 * @param[in]  to Point in 2D-Space the TranslateAnimation will end on.
		 */
		void setTo(sf::Vector2f to);

		/**
		 * @brief      Sets the MenuElement that the TranslateAnimation will translate.
		 *
		 * @param      menuElement  The MenuElement that the TranslateAnimation will translate.
		 */
		void setMenuElement(MenuElement* menuElement);

		/**
		 * @brief      Gets the MenuElement that the TranslateAnimation will translate.
		 *
		 * @return     The MenuElement that the TranslateAnimation will translate.
		 */
		MenuElement* getMenuElement() const;

		/**
		 * @brief      Returns whether or not the TranslateAnimation has successfully translated 
		 * 			   it's MenuElement to the end position.
		 *
		 * @return     True if the MenuElement is at the end position, otherwise false.
		 */
		bool isFinished() const;

	private:
		MenuElement* menuElement;	// The MenuElement that the TranslateAnimation will work on.
		sf::Vector2f from;			// The point in 2D-Space the TranslateAnimation will start from.
		sf::Vector2f to;			// The point in 2D-Space the TranslateAnimation will end on.
		sf::Vector2f intervall;		// The amount the MenuElement will be moved each update() call towards the end position.
		sf::Vector2f distance;		// Distance between from and to (start- and end position).
		bool doUpdate;				// Controls whether TranslateAnimation is updated in update().
		bool finished;				// Stores whether TranslateAnimation has successfully translated it's MenuElement 
									// to the end position.
		float duration;				// Stores how long the TranslateAnimation will take.
	};
}

#endif