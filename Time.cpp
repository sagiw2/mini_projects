#include "Time.h"
#include <array>
#include <ctime>
#include <chrono>


std::array<uint8_t, 6> TimeValue::toDigits() const
{
    return std::array<uint8_t,6>{
        static_cast<uint8_t>(hours / 10),
        static_cast<uint8_t>(hours % 10),
        static_cast<uint8_t>(minutes / 10),
        static_cast<uint8_t>(minutes % 10),
        static_cast<uint8_t>(seconds / 10),
        static_cast<uint8_t>(seconds % 10)
    };
}

uint8_t TimeValue::getSeconds() const
{
    return seconds;
}


TimeValue SystemTimeProvider::getCurrentSystemTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm local = *std::localtime(&t);

    return TimeValue{static_cast<uint8_t>(local.tm_hour),
                     static_cast<uint8_t>(local.tm_min),
                     static_cast<uint8_t>(local.tm_sec)};
}