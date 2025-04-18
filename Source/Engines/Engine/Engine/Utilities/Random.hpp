#pragma once

#include <random>

namespace Zengine
{
	namespace Random
	{
		template<typename T>
		T GetValue(const T& aMin, const T& aMax);
		
		template<typename T>
		T GetValue();
		
		
		template<typename T>
		T GetValue(const T& aMin, const T& aMax)
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<T> dist(aMin, aMax);

			return dist(mt);
		}

		template<typename T>
		T GetValue()
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

			return dist(mt);
		}
	}
}