#ifndef REALTIME_CLOCK_H
#define	REALTIME_CLOCK_H

class RealTimeDifference;
class RealTime;

#include <chrono>
#include "model/simulation_clock.h"

class RealTimeDifference
{
public:
    typedef std::chrono::steady_clock::duration Duration;
private:
    Duration duration;

public:
    explicit RealTimeDifference(const Duration&);
    const TimeDifference operator*(const TimePassageSpeed&) const;
    bool operator==(const RealTimeDifference&) const;
};


class RealTime
{
public:
    typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
private:
    TimePoint time_point;
public:
    explicit RealTime(const TimePoint&);
    static const RealTime now();
    const RealTimeDifference operator-(const RealTime&) const;
};

#endif	/* REALTIME_CLOCK_H */
