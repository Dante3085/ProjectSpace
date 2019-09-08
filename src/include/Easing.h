
#ifndef EASING_H
#define EASING_H

#include <functional>

namespace ProjectSpace
{
	namespace Easing
	{
		/* All Credit for the functions in this file goes to: https://github.com/jesusgollonet/ofpennereasing
		   This file provides functions for various ways of easing values from a startValue to an endValue.
		*/

#ifndef PI
#define PI  3.14159265
#endif

		/*
			t: elapsedTime (same unit as duration)
			b: startValue
			c: Difference between endValue and startValue
			d: duration
		*/
		using EasingFunction = std::function<float(float elapsedTime, float startValue, 
			                                       float deltaEndStartValue, float duration)>;

		float back_easeIn(float t, float b, float c, float d);
		float back_easeOut(float t, float b, float c, float d);
		float back_easeInOut(float t, float b, float c, float d);

		float bounce_easeOut(float t, float b, float c, float d);
		float bounce_easeIn(float t, float b, float c, float d);
		float bounce_easeInOut(float t, float b, float c, float d);

		float circ_easeIn(float t, float b, float c, float d);
		float circ_easeOut(float t, float b, float c, float d);
		float circ_easeInOut(float t, float b, float c, float d);

		float cubic_easeIn(float t, float b, float c, float d);
		float cubic_easeOut(float t, float b, float c, float d);
		float cubic_easeInOut(float t, float b, float c, float d);

		float elastic_easeIn(float t, float b, float c, float d);
		float elastic_easeOut(float t, float b, float c, float d);
		float elastic_easeInOut(float t, float b, float c, float d);

		float expo_easeIn(float t, float b, float c, float d);
		float expo_easeOut(float t, float b, float c, float d);
		float expo_easeInOut(float t, float b, float c, float d);

		float linear_easeNone(float t, float b, float c, float d);
		float linear_easeIn(float t, float b, float c, float d);
		float linear_easeOut(float t, float b, float c, float d);
		float linear_easeInOut(float t, float b, float c, float d);

		float quad_easeIn(float t, float b, float c, float d);
		float quad_easeOut(float t, float b, float c, float d);
		float quad_easeInOut(float t, float b, float c, float d);

		float quart_easeIn(float t, float b, float c, float d);
		float quart_easeOut(float t, float b, float c, float d);
		float quart_easeInOut(float t, float b, float c, float d);

		float quint_easeIn(float t, float b, float c, float d);
		float quint_easeOut(float t, float b, float c, float d);
		float quint_easeInOut(float t, float b, float c, float d);

		float sine_easeIn(float t, float b, float c, float d);
		float sine_easeOut(float t, float b, float c, float d);
		float sine_easeInOut(float t, float b, float c, float d);
	}
}

#endif