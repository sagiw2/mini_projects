#pragma once

#include "Time.h"

class ClockApp
{
protected:
    SystemTimeProvider systemTime;
    TimeValue currentTime{};
    TimeValue previousTime{};
public:
    virtual void run() = 0;
};