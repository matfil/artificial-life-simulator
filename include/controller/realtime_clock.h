#ifndef REALTIME_CLOCK_H
#define	REALTIME_CLOCK_H

#include <chrono>

class TimeDifference;
class TimePassageSpeed;
class RealTime;

class RealTimeClock
{
    const RealTime now() const;
};

class RealTimeDifference
{
public:
    typedef std::chrono::steady_clock::duration Duration;
private:
    Duration duration;

public:
    explicit RealTimeDifference(const Duration&);
    const TimeDifference operator*(const TimePassageSpeed&) const;
    const RealTime operator+(const RealTime&) const;
    bool operator==(const RealTimeDifference&) const;
    bool operator!=(const RealTimeDifference&) const;
    bool operator>(const RealTimeDifference&) const;
};


class RealTime
{
    friend class RealTimeDifference;
public:
    typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
private:
    TimePoint time_point;
public:
    RealTime(const TimePoint&);
    const RealTimeDifference operator-(const RealTime&) const;
    bool operator==(const RealTime&) const;
    bool operator!=(const RealTime&) const;
    bool operator>(const RealTime&) const;
    bool operator>=(const RealTime&) const;
};

#include "model/simulation_clock.h"

#endif	/* REALTIME_CLOCK_H */

