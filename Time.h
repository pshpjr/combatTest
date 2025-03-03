#pragma once

#include "Duration.h"
#include "Define.h"
using TimePoint = std::chrono::steady_clock::time_point;
using SteadyClock = std::chrono::steady_clock;
using Duration = std::chrono::duration<std::chrono::milliseconds>;
using MsTime = uint32;


/**
 * \return 이 함수가 처음으로 호출된 시간
 */
inline TimePoint GetApplicationStartTime()
{
	static const TimePoint startTime = SteadyClock::now();
	return startTime;
}

/**
 * \brief 프로그램이 시작하고 흐른 시간 ms
 * \return 
 */
inline MsTime getMSTime()
{
	using namespace std::chrono;

	return static_cast<uint32>(duration_cast<milliseconds>(steady_clock::now() - GetApplicationStartTime()).count());
}

inline MsTime getMSTimeDiff(MsTime oldMSTime, MsTime newMSTime)
{
	// 오버플로우 체크
	if (oldMSTime > newMSTime)
	{
		return 0xFFFFFFFF - oldMSTime + newMSTime;
	}
	return newMSTime - oldMSTime;
}

inline MsTime getMSTimeDiff(MsTime oldMSTime, TimePoint newTime)
{
	using namespace std::chrono;

	const MsTime newMSTime = static_cast<MsTime>(duration_cast<milliseconds>(newTime - GetApplicationStartTime()).
		count());
	return getMSTimeDiff(oldMSTime, newMSTime);
}

inline MsTime GetMSTimeDiffToNow(MsTime oldMSTime)
{
	return getMSTimeDiff(oldMSTime, getMSTime());
}

/**
 * \brief 주기적으로 발생하는 이벤트를 위한 타이머. reset해도 시간이 0이 되지 않음. 
 */
class IntervalTimer
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

	bool Passed() const
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

	time_t m_interval;
	time_t m_current;
};

/**
 * \brief 1회성 시간 만료를 확인하는 타이머
 */
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
