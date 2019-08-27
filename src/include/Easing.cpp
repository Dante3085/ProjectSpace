
#include "Easing.h"
#include <cmath>

namespace ProjectSpace
{
	namespace Easing
	{
		float back_easeIn(float t, float b, float c, float d)
		{
			float s = 1.70158f;
			float postFix = t /= d;
			return c * (postFix)* t * ((s + 1) * t - s) + b;
		}

		float back_easeOut(float t, float b, float c, float d)
		{
			float s = 1.70158f;
			return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
		}

		float back_easeInOut(float t, float b, float c, float d)
		{
			float s = 1.70158f;
			if ((t /= d / 2) < 1) return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
			float postFix = t -= 2;
			return c / 2 * ((postFix)* t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
		}

		float bounce_easeOut(float t, float b, float c, float d)
		{
			if ((t /= d) < (1 / 2.75f)) {
				return c * (7.5625f * t * t) + b;
			}
			else if (t < (2 / 2.75f)) {
				float postFix = t -= (1.5f / 2.75f);
				return c * (7.5625f * (postFix)* t + .75f) + b;
			}
			else if (t < (2.5 / 2.75)) {
				float postFix = t -= (2.25f / 2.75f);
				return c * (7.5625f * (postFix)* t + .9375f) + b;
			}
			else {
				float postFix = t -= (2.625f / 2.75f);
				return c * (7.5625f * (postFix)* t + .984375f) + b;
			}
		}

		float bounce_easeIn(float t, float b, float c, float d)
		{
			return c - bounce_easeOut(d - t, 0, c, d) + b;
		}

		float bounce_easeInOut(float t, float b, float c, float d)
		{
			if (t < d / 2) return bounce_easeIn(t * 2, 0, c, d) * .5f + b;
			else return bounce_easeOut(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
		}

		float circ_easeIn(float t, float b, float c, float d)
		{
			return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
		}

		float circ_easeOut(float t, float b, float c, float d)
		{
			return c * sqrt(1 - (t = t / d - 1) * t) + b;
		}

		float circ_easeInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
			return c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
		}

		float cubic_easeIn(float t, float b, float c, float d)
		{
			return c * (t /= d) * t * t + b;
		}

		float cubic_easeOut(float t, float b, float c, float d)
		{
			return c * ((t = t / d - 1) * t * t + 1) + b;
		}

		float cubic_easeInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
			return c / 2 * ((t -= 2) * t * t + 2) + b;
		}

		float elastic_easeIn(float t, float b, float c, float d)
		{
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;
			float p = d * .3f;
			float a = c;
			float s = p / 4;
			float postFix = a * pow(2, 10 * (t -= 1)); // this is a fix, again, with post-increment operators
			return -(postFix * sin((t * d - s) * (2 * PI) / p)) + b;
		}

		float elastic_easeOut(float t, float b, float c, float d)
		{
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;
			float p = d * .3f;
			float a = c;
			float s = p / 4;
			return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * PI) / p) + c + b);
		}

		float elastic_easeInOut(float t, float b, float c, float d)
		{
			if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
			float p = d * (.3f * 1.5f);
			float a = c;
			float s = p / 4;

			if (t < 1)
			{
				float postFix = a * pow(2, 10 * (t -= 1)); // postIncrement is evil
				return -.5f * (postFix * sin((t * d - s) * (2 * PI) / p)) + b;
			}
			float postFix = a * pow(2, -10 * (t -= 1)); // postIncrement is evil
			return postFix * sin((t * d - s) * (2 * PI) / p) * .5f + c + b;
		}

		float expo_easeIn(float t, float b, float c, float d)
		{
			return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
		}

		float expo_easeOut(float t, float b, float c, float d)
		{
			return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
		}

		float expo_easeInOut(float t, float b, float c, float d)
		{
			if (t == 0) return b;
			if (t == d) return b + c;
			if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
			return c / 2 * (-pow(2, -10 * --t) + 2) + b;
		}

		float linear_easeNone(float t, float b, float c, float d)
		{
			return c * t / d + b;
		}

		float linear_easeIn(float t, float b, float c, float d)
		{
			return c * t / d + b;
		}

		float linear_easeOut(float t, float b, float c, float d)
		{
			return c * t / d + b;
		}

		float linear_easeInOut(float t, float b, float c, float d) {
			return c * t / d + b;
		}

		/*
			t: elapsedTime (same unit as duration)
			b: startValue
			c: Difference between endValue and startValue
			d: duration
		*/
		float quad_easeIn(float t, float b, float c, float d)
		{
			return c * (t /= d) * t + b;
		}

		float quad_easeOut(float t, float b, float c, float d)
		{
			return -c * (t /= d) * (t - 2) + b;
		}

		float quad_easeInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1) return ((c / 2) * (t * t)) + b;
			return -c / 2 * (((t - 2) * (--t)) - 1) + b;
		}

		float quart_easeIn(float t, float b, float c, float d)
		{
			return c * (t /= d) * t * t * t + b;
		}

		float quart_easeOut(float t, float b, float c, float d)
		{
			return -c * ((t = t / d - 1) * t * t * t - 1) + b;
		}

		float quart_easeInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1) return c / 2 * t * t * t * t + b;
			return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
		}

		float quint_easeIn(float t, float b, float c, float d)
		{
			return c * (t /= d) * t * t * t * t + b;
		}

		float quint_easeOut(float t, float b, float c, float d)
		{
			return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
		}

		float quint_easeInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1) return c / 2 * t * t * t * t * t + b;
			return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
		}

		float sine_easeIn(float t, float b, float c, float d)
		{
			return -c * cos(t / d * (PI / 2)) + c + b;
		}

		float sine_easeOut(float t, float b, float c, float d)
		{
			return c * sin(t / d * (PI / 2)) + b;
		}

		float sine_easeInOut(float t, float b, float c, float d)
		{
			return -c / 2 * (cos(PI * t / d) - 1) + b;
		}
	}
}