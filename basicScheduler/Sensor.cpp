#include "Sensor.h"
#include <iostream>


void Sensor::sample(const TimePoint startTime)
{
    std::cout <<"[" <<
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() <<
    "ms]: sampling sensor, data= " << counter <<std::endl;
    counter++;
}