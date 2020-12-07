#include "ToDoItem.h"

ToDoItem::ToDoItem(ToDoItem::sys_time &timePoint,
                   std::string_view message)
                   : _timePoint(timePoint), _message(message) {}

PeriodicToDoItem::PeriodicToDoItem(ToDoItem::sys_time &timePoint,
                                   std::string_view message,
                                   long quantity,
                                   NotificationPeriod period)
                                   : ToDoItem(timePoint, message), _quantity(quantity),
                                   _period(period) {}

ItemBuilder& ItemBuilder::setTime(ToDoItem::sys_time &time)
{
    _time = time;
    return *this;
}

ItemBuilder& ItemBuilder::setMessage(const std::string &message)
{
    _message = message;
    return *this;
}

ItemBuilder& ItemBuilder::setPeriod(long quantity, NotificationPeriod period)
{
    _quantity = quantity;
    _period = period;
    return *this;
}

std::unique_ptr<ToDoItem> ItemBuilder::build()
{
    return _period == NotificationPeriod::once ?
        std::make_unique<ToDoItem>(_time, _message) :
        std::make_unique<PeriodicToDoItem>(_time, _message, _quantity, _period);
}
