#include "Scheduler.h"
#include "LED.h"
#include "Sensor.h"
#include "OneShot.h"
#include "Comm.h"
#include <thread>


int main()
{
    Scheduler sche;
    Sensor sensor;
    LED led;
    OneShot oneShot;
    Comm comm;


    auto startTime = std::chrono::steady_clock::now();
    // sche.schedulePeriodic(Duration(200), [&sensor, startTime]() { sensor.sample(startTime); });
    // sche.schedulePeriodic(Duration(300), [&led, startTime]() { led.toggle(startTime); });
    // sche.scheduleOneShot(startTime + Duration(600), [&oneShot, startTime]() { oneShot.activate(startTime);});
    TaskID timeoutMsgTaskID = sche.scheduleOneShot(startTime + Duration(500), [&comm, startTime]() { comm.onTimeout(startTime);} );
    sche.scheduleOneShot(startTime + Duration(200), [&sche, &comm, timeoutMsgTaskID, startTime]() { comm.onMessageReceived(startTime);
                                                                                                    sche.reschedule(timeoutMsgTaskID,std::chrono::steady_clock::now() + Duration(500)); });
    sche.scheduleOneShot(startTime + Duration(400), [&sche, &comm, timeoutMsgTaskID, startTime]() { comm.onMessageReceived(startTime);
                                                                                                    sche.reschedule(timeoutMsgTaskID,std::chrono::steady_clock::now() + Duration(500)); });
    sche.scheduleOneShot(startTime + Duration(700), [&sche, &comm, timeoutMsgTaskID, startTime]() { comm.onMessageReceived(startTime);
                                                                                                    sche.reschedule(timeoutMsgTaskID,std::chrono::steady_clock::now() + Duration(500)); });
    sche.runFor(Duration(2000));
    return 0;
}