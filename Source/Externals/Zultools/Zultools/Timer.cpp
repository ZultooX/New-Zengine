#include "Timer.h"

#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace CommonUtilities
{
	Timer::Timer() : myStartingTime(high_resolution_clock::now())
	{
		myLastTime = high_resolution_clock::now();
	}

	void Timer::Update()
	{
		// Calculate time since last frame.
		steady_clock::time_point currentTime = high_resolution_clock::now();
		milliseconds durationSinceLastFrame = duration_cast<milliseconds>(currentTime - myLastTime);

		// Calculate delta time.
		myDeltaTime = static_cast<float>(durationSinceLastFrame.count() * MillisecondsToSeconds);

		myLastTime = currentTime;
	}

	float Timer::GetDeltaTime() const
	{
		return myDeltaTime;
	}

	double Timer::GetTotalTime() const
	{
		// Calculate total time active.
		steady_clock::time_point currentTime = high_resolution_clock::now();
		milliseconds totalTime = duration_cast<milliseconds>(currentTime - myStartingTime);

		return static_cast<double>(totalTime.count() * MillisecondsToSeconds);
	}
}