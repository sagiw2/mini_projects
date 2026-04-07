#pragma once

#include <list>
#include "Task.h"


class Scheduler {
private:
    std::list<Task> tasks;
    TaskID nextTaskID{0};

    void insertToTasksList(Task task);

public:
    TaskID schedulePeriodic(const Duration& interval, const std::function<void(void)> callback);
    TaskID scheduleOneShot(const TimePoint& activationTime, const std::function<void(void)> callback);
    void runFor(const Duration& duration);
    bool cancel(const TaskID);
};