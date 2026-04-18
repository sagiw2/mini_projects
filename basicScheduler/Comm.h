#pragma once
#include "Task.h"

class Comm
{
private:
    int receivedMessageCount{0};
    bool timedOut{false};

public:
    void onMessageReceived(const TimePoint startTime);
    void onTimeout(const TimePoint startTime);
};