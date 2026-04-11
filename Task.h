#pragma once
#include <chrono>
#include <functional>

using Duration = std::chrono::milliseconds;
using TimePoint = std::chrono::steady_clock::time_point;
using TaskID = std::uint32_t;

enum class TaskType
{
    OneShot,
    Periodic,
};

struct Task {
    TaskType type;
    TaskID id;
    TimePoint nextExecutionTime;
    Duration interval;
    std::function<void(void)> callback;
};