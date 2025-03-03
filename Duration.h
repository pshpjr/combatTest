#pragma once
#include <chrono>
using Milliseconds = std::chrono::milliseconds;
using FloatMilliseconds = std::chrono::duration<float, Milliseconds::period>;

using Seconds = std::chrono::seconds;
using FloatSeconds = std::chrono::duration<float, Seconds::period>;

using Minutes = std::chrono::minutes;
using FloatMinutes = std::chrono::duration<float, Minutes::period>;

using Hours = std::chrono::hours;
using FloatHours = std::chrono::duration<float, Hours::period>;

using TimePoint = std::chrono::steady_clock::time_point;
using SystemTimePoint = std::chrono::system_clock::time_point;

//전역적으로 리터럴 사용 허용
using namespace std::chrono_literals;

constexpr std::chrono::days operator""_days(unsigned long long days)
{
	return std::chrono::days(days);
}
