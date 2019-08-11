
#ifndef TRANSLATE_ANIMATION
#define TRANSLATE_ANIMATION

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Button.h"
#include "Log.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for smoothly translating MenuElements from one point in 2D-Space to another.
	 */
	class TranslateAnimation : public Entity
	{
	public:

		/**
		 * @brief      Constructs a TranslateAnimation that can translate the given MenuElement from 'from' to 'to'.
		 *
		 * @param      menuElement  The menu element
		 * @param[in]  from         The point in 2D-Space the TranslateAnimation will start from.
		 * @param[in]  to           The point in 2D-Space the TranslateAnimation will end on.
		 * from 'from' to 'to'.
		 * @param[in]  velocityModifier Scalar multiplied with distance vector between MenuElement and to. This will dictate the step
		 * the MenuElement is moved each update.
		 */
		TranslateAnimation(MenuElement* menuElement, sf::Vector2f const& from, sf::Vector2f const& to, float duration);

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

		bool isUpdating() const;

		/**
		 * @brief      Sets from<->to so that the Translation now happens in reverse.
		 */
		void reverse();

	private:
		MenuElement* menuElement;	// The MenuElement that the TranslateAnimation will work on.
		sf::Vector2f from;			// The point in 2D-Space the TranslateAnimation will start from.
		sf::Vector2f to;			// The point in 2D-Space the TranslateAnimation will end on.
		float duration;
		float elapsedTime;
		float minDistance;          /* The threshold at which the Translation process is stopped
									   and the menuElement's position just gets set to "to". */
		bool doUpdate;				// Controls whether TranslateAnimation is updated in update().
		bool finished;				/* Stores whether TranslateAnimation has successfully translated it's MenuElement
									   to the end position. */

		float velocityModifier;       // The factor with which the velocity decreases each tick.
		sf::Vector2f currentVelocity; // The value with which the menuElement's position is modified each tick.
		sf::Vector2f minVelocity;     // The threshold at which the velocity is reset to its initial value.

		Log* log;

	private:

		/*
			t: elapsedTime (same unit as duration)
			b: startValue
			c: Difference between endValue and startValue
			d: duration
		*/
		float easeInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1) return ((c / 2) * (t * t)) + b;
			return -c / 2 * (((t - 2) * (--t)) - 1) + b;

		}
	};
}

#endif