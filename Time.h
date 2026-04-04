#pragma once

#include <cstdint>
#include <array>


class TimeValue
{
private:
    uint8_t hours{};
    uint8_t minutes{};
    uint8_t seconds{};
public:
    TimeValue() {};
    TimeValue(uint8_t hours, uint8_t minutes, uint8_t seconds) : hours(hours), minutes(minutes), seconds(seconds) {};

    std::array<uint8_t, 6> toDigits() const;

    uint8_t getSeconds() const;

    bool operator<(const TimeValue& other) const
    {
        if (hours != other.hours) return hours < other.hours;
        if (minutes != other.minutes) return minutes < other.minutes;
        return seconds < other.seconds;
    }
};

class SystemTimeProvider
{
public:
    TimeValue getCurrentSystemTime();
};