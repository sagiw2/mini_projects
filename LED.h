#pragma once
#include "Task.h"

class LED
{
private:
    bool isOn{false};
public:
    void toggle(const TimePoint startTime);
};