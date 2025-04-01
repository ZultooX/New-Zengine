#pragma once

#include <chrono>

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;

		void Update();

		float GetDeltaTime() const;
		double GetTotalTime() const;

	private:
		const float MillisecondsToSeconds = 0.001f;
	
		const std::chrono::high_resolution_clock::time_point myStartingTime;

		std::chrono::high_resolution_clock::time_point myLastTime;

		float myDeltaTime = 0;
	};
} 