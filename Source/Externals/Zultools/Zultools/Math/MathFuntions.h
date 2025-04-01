#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <assert.h>
#include <stdint.h>
#include <math.h>

namespace Math
{
#define PI 3.14159265358979323846f
	constexpr float Pi = 3.14159265358979323846f;
	constexpr float Pi_Half = Pi / 2.f;
	constexpr float _DegToRad = Pi / 180.f;
	constexpr float _RadToDeg = 180.f / Pi;

	constexpr float SmallNumber = (1.e-8f);
	constexpr float KindaSmallNumber = (1.e-4f);

	constexpr float Tau = Pi * 2.0f;
	constexpr double PiD = 3.1415926535897932384626433832795;
	constexpr double PiHalfD = PiD * 0.5;
	constexpr double TauD = PiD * 2.0;

	template <typename T>
	T MapValue(T aRangeMin, T aRangeMax, T aValueMin, T aValueMax, T aValue)
	{
		float returnValue = ((aValue - aValueMin) * (aRangeMax - aRangeMin) / (aValueMax - aValueMin)) + aRangeMin;

		return returnValue;
	}

	template <typename T>
	inline T Max(const T aValue, const T someAnotherValue)
	{
		return (aValue > someAnotherValue) ? aValue : someAnotherValue;
	}

	template <typename T>
	inline T Min(const T aValue, const T someAnotherValue)
	{
		return (aValue < someAnotherValue) ? aValue : someAnotherValue;
	}

	template <typename T>
	inline T Abs(T aValue)
	{
		return (aValue < 0) ? (-aValue) : aValue;
	}

	template <typename T>
	inline T Clamp(T aValue, const T aMin, const T aMax)
	{
		assert(aMin <= aMax && "The minimun must be larger then the max.");

		// Clamps the value between aMin and aMax.
		return (aValue > aMax) ? (aValue = aMax) : ((aValue < aMin) ? (aValue = aMin) : aValue);
	}

	template <typename T>
	inline T Lerp(const T aStartingValue, const T aTargetValue, float someProgress)
	{
		return (aStartingValue + someProgress * (aTargetValue - aStartingValue));
	}

	template <typename T>
	inline float InvLerp(const T aStartingValue, const T aTargetValue, float aValueBetween)
	{
		return (aValueBetween - aStartingValue) / (aTargetValue - aStartingValue);
	}

	template <typename T>
	inline void Swap(T &aValue, T &someAnotherValue)
	{
		T temp = aValue;
		aValue = someAnotherValue;
		someAnotherValue = temp;
	}

	inline float RadToDeg(const float &someRadians)
	{
		return someRadians * (float)(180.0f / PI);
	}

	inline float DegToRad(const float &someDeegrees)
	{
		return someDeegrees * (float)(PI / 180.0f);
	}

	inline int Factorial(const int n)
	{
		if (n == 0)
			return 1;

		return n * Factorial(n - 1);
	}

	typedef struct { uint64_t state;  uint64_t inc; } pcg32_random_t;

	inline uint32_t pcg32_random_r(pcg32_random_t* rng)
	{
		uint64_t oldstate = rng->state;
		// Advance internal state
		rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
		// Calculate output function (XSH RR), uses old state for max ILP
		uint32_t xorshifted = (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
		uint32_t rot = oldstate >> 59u;
		return (xorshifted >> rot) | (xorshifted << ((rot) & 31));
	}
	inline float RandomFloat()
	{
		thread_local pcg32_random_t state;
		return (float)ldexp(pcg32_random_r(&state), -32);
	}

	inline int BinomialCoefficient(const int n, const int i)
	{
		assert(i <= n && "'i' cant be higher then 'n'");

		int top = Factorial(n);
		int bottom = Factorial(i) * Factorial(n - i);

		return top / bottom;
	}
}
#endif