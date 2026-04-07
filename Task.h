#pragma once
#include <chrono>
#include <functional>

using Duration = std::chrono::milliseconds;
using TimePoint = std::chrono::steady_clock::time_point;

enum class TaskType
{
    OneShot,
    Periodic,
};

struct Task {
    std::function<void(void)> callback;
    Duration interval;
    TimePoint nextExecutionTime;
    TaskType type;
};