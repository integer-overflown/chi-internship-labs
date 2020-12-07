#pragma once
#include <chrono>
#include <string>
#include <memory>

enum class NotificationPeriod
{
    once, minute, hour, day, week, month
};

struct ToDoItem
{
    using sys_time = std::chrono::time_point<std::chrono::system_clock>;
    sys_time _timePoint;
    std::string _message;
    ToDoItem(sys_time&, std::string_view);
};

struct PeriodicToDoItem : public ToDoItem
{
    long _quantity;
    NotificationPeriod _period;
    PeriodicToDoItem(sys_time&, std::string_view, long, NotificationPeriod);
};

class ItemBuilder
{
public:
    ItemBuilder& setTime(ToDoItem::sys_time&);
    ItemBuilder& setMessage(const std::string&);
    ItemBuilder& setPeriod(long, NotificationPeriod);
    std::unique_ptr<ToDoItem> build();

private:
    std::string_view _message;
    ToDoItem::sys_time _time;
    NotificationPeriod _period { NotificationPeriod::once };
    long _quantity;
};
