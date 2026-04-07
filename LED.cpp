#include "LED.h"
#include <iostream>

void LED::toggle(TimePoint startTime)
{
    isOn = !isOn;
    std::cout << "[" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() << "ms]: the LED turned " << (isOn ? "on" : "off") << std::endl;
}