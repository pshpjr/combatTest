#pragma once

#include "Duration.h"
#include "Define.h"
using TimePoint = std::chrono::steady_clock::time_point;
using SteadyClock = std::chrono::steady_clock;
using Duration = std::chrono::duration<std::chrono::milliseconds>;

inline TimePoint GetApplicationStartTime()
{
	static const TimePoint startTime = SteadyClock::now();
	return startTime;
}

inline uint32 getMSTime()
{
	using namespace std::chrono;

	return static_cast<uint32>(duration_cast<milliseconds>(steady_clock::now() - GetApplicationStartTime()).count());
}

inline uint32 getMSTimeDiff(uint32 oldMSTime, uint32 newMSTime)
{
	// getMSTime() have limited data range and this is case when it overflow in this tick
	if (oldMSTime > newMSTime)
	{
		return 0xFFFFFFFF - oldMSTime + newMSTime;
	}
	return newMSTime - oldMSTime;
}

inline uint32 getMSTimeDiff(uint32 oldMSTime, TimePoint newTime)
{
	using namespace std::chrono;

	const uint32 newMSTime = static_cast<uint32>(duration_cast<milliseconds>(newTime - GetApplicationStartTime()).
		count());
	return getMSTimeDiff(oldMSTime, newMSTime);
}

inline uint32 GetMSTimeDiffToNow(uint32 oldMSTime)
{
	return getMSTimeDiff(oldMSTime, getMSTime());
}

struct IntervalTimer
{
	IntervalTimer()
		: m_interval(0), m_current(0)
	{
	}

	void Update(time_t diff)
	{
		m_current += diff;
		if (m_current < 0)
		{
			m_current = 0;
		}
	}

	bool Passed()
	{
		return m_current >= m_interval;
	}

	void Reset()
	{
		if (m_current >= m_interval)
		{
			m_current %= m_interval;
		}
	}

	void SetCurrent(time_t current)
	{
		m_current = current;
	}

	void SetInterval(time_t interval)
	{
		m_interval = interval;
	}

	[[nodiscard]] time_t GetInterval() const
	{
		return m_interval;
	}

	[[nodiscard]] time_t GetCurrent() const
	{
		return m_current;
	}

private:
	time_t m_interval;
	time_t m_current;
};

struct TimeTracker
{
	TimeTracker(int32 expiry = 0) : m_expiryTime(expiry)
	{
	}

	TimeTracker(Milliseconds expiry) : m_expiryTime(expiry)
	{
	}

	void Update(int32 diff)
	{
		Update(Milliseconds(diff));
	}

	void Update(Milliseconds diff)
	{
		m_expiryTime -= diff;
	}

	[[nodiscard]] bool Passed() const
	{
		return m_expiryTime <= 0s;
	}

	void Reset(int32 expiry)
	{
		Reset(Milliseconds(expiry));
	}

	void Reset(Milliseconds expiry)
	{
		m_expiryTime = expiry;
	}

	[[nodiscard]] Milliseconds GetExpiry() const
	{
		return m_expiryTime;
	}

private:
	Milliseconds m_expiryTime;
};

struct PeriodicTimer
{
	PeriodicTimer(int32 period, int32 start_time)
		: m_period(period), m_expireTime(start_time)
	{
	}

	bool Update(const uint32 diff)
	{
		if ((m_expireTime -= diff) > 0)
		{
			return false;
		}

		m_expireTime += m_period > static_cast<int32>(diff) ? m_period : diff;
		return true;
	}

	void SetPeriodic(int32 period, int32 start_time)
	{
		m_expireTime = start_time;
		m_period = period;
	}

	// Tracker interface
	void TUpdate(int32 diff)
	{
		m_expireTime -= diff;
	}

	[[nodiscard]] bool TPassed() const
	{
		return m_expireTime <= 0;
	}

	void TReset(int32 diff, int32 period)
	{
		m_expireTime += period > diff ? period : diff;
	}

private:
	int32 m_period;
	int32 m_expireTime;
};
