#include "Scheduler.h"
#include "LED.h"
#include "Sensor.h"
#include "OneShot.h"


int main()
{
    Scheduler sche;
    Sensor sensor;
    LED led;
    OneShot oneShot;

    auto startTime = std::chrono::steady_clock::now();
    sche.schedulePeriodic(Duration(200), [&sensor, startTime]() { sensor.sample(startTime); });
    sche.schedulePeriodic(Duration(300), [&led, startTime]() { led.toggle(startTime); });
    sche.scheduleOneShot(startTime + Duration(600), [&oneShot, startTime]() { oneShot.activate(startTime);});
    sche.runFor(Duration(1000));
    return 0;
}