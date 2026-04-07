#pragma once

#include "Task.h"

class Sensor
{
private:
    int counter{0};
public:
    void sample(TimePoint startTime);
};