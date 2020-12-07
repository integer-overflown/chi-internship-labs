#pragma once
#include <chrono>
#include <string>
#include "ToDoItem.h"

class TimeParser
{
public:
    enum status {
        ok, unrecognized
    };
    static constexpr const char* one_time_fmt = "%Y-%m-%d %H:%M";
    static status parse(const std::string&, ItemBuilder&);

private:
    static NotificationPeriod stringToPeriod(const std::string&);
};
