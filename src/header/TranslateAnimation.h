
#ifndef TRANSLATE_ANIMATION
#define TRANSLATE_ANIMATION

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Button.h"
#include "Log.h"

namespace ProjectSpace
{
	enum Easing
	{
		BACK_EASE_IN,
		BACK_EASE_OUT,
		BACK_EASE_IN_OUT,

		BOUNCE_EASE_IN,
		BOUNCE_EASE_OUT,
		BOUNCE_EASE_IN_OUT,

		CIRC_EASE_IN,
		CIRC_EASE_OUT,
		CIRC_EASE_IN_OUT,

		CUBIC_EASE_IN,
		CUBIC_EASE_OUT,
		CUBIC_EASE_IN_OUT,

		ELASTIC_EASE_IN,
		ELASTIC_EASE_OUT,
		ELASTIC_EASE_IN_OUT,

		EXPO_EASE_IN,
		EXPO_EASE_OUT,
		EXPO_EASE_IN_OUT,

		LINEAR_EASE_NONE,
		LINEAR_EASE_IN,
		LINEAR_EASE_OUT,
		LINEAR_EASE_IN_OUT,

		QUAD_EASE_IN,
		QUAD_EASE_OUT,
		QUAD_EASE_IN_OUT,

		QUINT_EASE_IN,
		QUINT_EASE_OUT,
		QUINT_EASE_IN_OUT,

		SINE_EASE_IN,
		SINE_EASE_OUT,
		SINE_EASE_IN_OUT,
	};

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

		void setEasing(Easing easing);

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

		float getDuration() const;

		void setDuration(float duration);

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
		bool doUpdate;				// Controls whether TranslateAnimation is updated in update().

		sf::Vector2f currentVelocity; // The value with which the menuElement's position is modified each tick.
		std::function<float(float t, float b, float c, float d)> easingFunction;

		Log* log;
	};
}

#endif