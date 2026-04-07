#include <iostream>
#include "OneShot.h"

void OneShot::activate(TimePoint startTime)
{
    std::cout <<"[" <<
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() <<
    "ms]: one shot task " << std::endl;
}