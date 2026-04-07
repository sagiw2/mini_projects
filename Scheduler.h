#pragma once

#include <list>
#include "Task.h"


class Scheduler {
private:
    std::list<Task> tasks;

    void insertToTasksList(Task task);

public:
    void schedulePeriodic(const Duration& interval, const std::function<void(void)> callback);
    void scheduleOneShot(const TimePoint& activationTime, const std::function<void(void)> callback);
    void runFor(const Duration& duration);
};