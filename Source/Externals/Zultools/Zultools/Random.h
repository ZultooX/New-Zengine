#ifndef RANDOM_H
#define RANDOM_H

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <random>
#include <numeric>

class  Random
{
public:
	template<typename T>
	inline static T GetValue()
	{
		std::random_device rd;
		std::mt19937 eng(rd());

		std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

		return distribution(eng);
	}

	template<typename T>
	inline static T GetValue(T aMin, T aMax)
	{
		static std::mt19937 gen(std::random_device{}());
		static std::uniform_real_distribution<> dis(0.0, 1.0);

		return std::round(dis(gen) * (aMax - aMin + 1)) + aMin - 1;
	}

	inline static float GetFloat(float min = 0.0f, float max = 1.0f)
	{
		static std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<> dis(min, max);
		return (float)dis(gen);
	}
};
#endif