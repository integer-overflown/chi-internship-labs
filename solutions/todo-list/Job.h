#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <atomic>

class Job
{
public:
    using runnable = std::function<void()>;
    enum status { cancelled, scheduled, idle };
    template<typename Callable, typename... Args>
    explicit Job(Callable&& job, Args&&... args);
    ~Job();
    void runAt(const std::chrono::time_point<std::chrono::system_clock> &time);
    void cancel();
    status getStatus();

private:
    runnable _job;
    status _status { idle };
    std::atomic_bool canceled {false};
    std::condition_variable conditional{};
    std::mutex job_lock{};
};

template<typename Callable, typename... Args>
Job::Job(Callable &&job, Args&&... args)
{
    _job = std::bind(job, args...);
}

