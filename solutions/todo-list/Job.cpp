#include "Job.h"

void Job::runAt(const std::chrono::time_point<std::chrono::system_clock> &time)
{
    std::thread([&time, this]() {
        std::unique_lock<std::mutex> lck(job_lock);
        conditional.wait_until(lck, time, [this]() { return canceled.load(); });
        if (canceled) {
            _status = cancelled;
        } else {
            _job();
            _status = idle;
        }
        conditional.notify_all();
    }).detach();
}


void Job::cancel()
{
    canceled.store(true);
}

Job::~Job()
{
    std::unique_lock<std::mutex> lck(job_lock);
    cancel();
    conditional.notify_all();
}

Job::status Job::getStatus() {
    return _status;
}

