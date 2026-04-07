#include "Scheduler.h"
#include <chrono>
#include <vector>
#include <thread>


void Scheduler::insertToTasksList(Task task)
{
    auto pos = std::find_if(tasks.begin(), tasks.end(),
                            [&](const auto& t) {
                                return t.nextExecutionTime > task.nextExecutionTime;
                            });
    tasks.insert(pos, std::move(task));
}

void Scheduler::schedulePeriodic(const Duration& interval, const std::function<void(void)> callback)
{
    // Task newTask{callback, interval, std::chrono::steady_clock::now() + interval, TaskType::Periodic};
    Task newTask{TaskType::Periodic, nextTaskID, std::chrono::steady_clock::now() + interval, interval, callback};
    insertToTasksList(std::move(newTask));
    return nextTaskID++;
}

void Scheduler::scheduleOneShot(const TimePoint& activationTime, const std::function<void(void)> callback)
{
    // insertToTasksList(Task{callback, static_cast<Duration>(0), activationTime, TaskType::OneShot});
    insertToTasksList(Task{TaskType::OneShot, nextTaskID, activationTime, static_cast<Duration>(0), callback});
    return nextTaskID++;
}

void Scheduler::runFor(const Duration& duration)
{
    auto now = std::chrono::steady_clock::now();
    auto endTime = now + duration;
    while (now < endTime && !tasks.empty())
    {
        std::vector<Task> dueTasks;

        auto wakeUpTime = std::min(endTime, tasks.front().nextExecutionTime);
        auto sleepDuration = wakeUpTime - now;
        std::this_thread::sleep_for(sleepDuration);
        now = std::chrono::steady_clock::now();

        while (!tasks.empty() && tasks.front().nextExecutionTime <= now)
        {
            dueTasks.emplace_back(std::move(tasks.front()));
            tasks.pop_front();
        }
        for (Task& task : dueTasks)
        {
            task.callback();
            if (task.type == TaskType::Periodic)
            {
                task.nextExecutionTime += task.interval;
                insertToTasksList(std::move(task));
            }
        }
        now = std::chrono::steady_clock::now();
    }
}

bool Scheduler::cancel(const TaskID idToRemove)
{
    auto taskIdx = std::find_if(tasks.begin(), tasks.end(), [idToRemove] (const Task& task) {return task.id == idToRemove;} );
    if (taskIdx != tasks.end())
    {
        tasks.erase(taskIdx);
        return true;
    }
    return false;
}
