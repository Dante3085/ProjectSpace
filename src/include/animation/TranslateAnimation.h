
#ifndef TRANSLATE_ANIMATION_H
#define TRANSLATE_ANIMATION_H

#include <SFML/System/Vector2.hpp>

#include "animation/Translatable.h"
#include "animation/Easing.h"
#include "scenes/Entity.h"
#include "utility/Log.h"

namespace ProjectSpace
{
	/**
	 * @brief      Class for smoothly translating Translatables from one point in 2D-Space to another.
	 */
	class TranslateAnimation : public Entity
	{
	public:

		/**
		 * @brief      Constructs a TranslateAnimation that can translate the given Translatable from 'from' to 'to'.
		 *
		 * @param      Translatable  The Translatable.
		 * @param[in]  from         The point in 2D-Space the TranslateAnimation will start from.
		 * @param[in]  to           The point in 2D-Space the TranslateAnimation will end on.
		 * from 'from' to 'to'.
		 * @param[in]  velocityModifier Scalar multiplied with distance vector between Translatable and to. This will dictate the step
		 * the Translatable is moved each update.
		 */
		TranslateAnimation(Translatable& translatable, sf::Vector2f const& from = sf::Vector2f{0, 0},
		sf::Vector2f const& to = sf::Vector2f{50, 0}, float duration = 1000);

		/**
		 * @brief      Updates the TranslateAnimation each frame.
		 *
		 * @param[in]  time  The time that has passed since last update call.
		 */
		void update(sf::Time time) override;

		void setEasingFunction(Easing::EasingFunction easingFunction);

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
		 * @problem    Not sure if this function should set the Translatable to from. This function is subject to change.
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
		 * @brief      Sets the Translatable that the TranslateAnimation will translate.
		 *
		 * @param      Translatable  The Translatable that the TranslateAnimation will translate.
		 */
		void setTranslatable(Translatable& translatable);

		/**
		 * @brief      Gets the Translatable that the TranslateAnimation will translate.
		 *
		 * @return     The Translatable that the TranslateAnimation will translate.
		 */
		Translatable& getTranslatable() const;

		float getDuration() const;

		void setDuration(float duration);

		float getElapsedTime() const;

		bool isUpdating() const;

		/**
		 * @brief      Sets from<->to so that the Translation now happens in reverse.
		 */
		void reverse();

	private:
		Translatable& translatable;	// The Translatable that the TranslateAnimation will work on.
		sf::Vector2f from;			// The point in 2D-Space the TranslateAnimation will start from.
		sf::Vector2f to;			// The point in 2D-Space the TranslateAnimation will end on.
		float duration;
		float elapsedTime;
		bool doUpdate;				// Controls whether TranslateAnimation updates itself.

		sf::Vector2f currentVelocity; // The value with which the Translatable's position is modified each update() call.
		Easing::EasingFunction easingFunction;

		Log* log;
	};
}

#endif