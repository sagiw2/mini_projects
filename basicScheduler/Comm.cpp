#include "Comm.h"
#include <iostream>

void Comm::onMessageReceived(const TimePoint startTime)
{
    ++receivedMessageCount;
    std::cout << "[" <<
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() <<
    "ms]: message received, total: " << receivedMessageCount << std::endl;
}

void Comm::onTimeout(const TimePoint startTime)
{
    timedOut = true;
    std::cout << "[" <<
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() <<
    "ms]: no messages received - communication timeout" << std::endl;
}
