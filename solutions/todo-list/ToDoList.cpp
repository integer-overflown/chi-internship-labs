#include "ToDoList.h"
#include <memory>

void ToDoList::addItem(value_type&& item)
{
    std::unique_lock<std::mutex> lock(_items_lock);
    auto key = std::chrono::system_clock::to_time_t(item->_timePoint);
    auto pos = items.insert({ key, std::move(item) });
    if (items.begin() == pos.first && _guard)
        _guard->schedule(key);
}

ToDoList::iterator ToDoList::begin() {
    return items.cbegin();
}

ToDoList::iterator ToDoList::end() {
    return items.cend();
}

void ToDoList::setCallback(callback_t &&callback)
{
    _guard = std::make_unique<NotificationGuard>(*this, std::move(callback));
}

void ToDoList::popTask(id_t id) {
    std::unique_lock<std::mutex> lock(_items_lock);
    auto item = items.find(id);
    items.erase(item->first); // TODO

    if (!items.empty() && _guard) {
        auto new_id = items.begin()->first;
        _guard->schedule(new_id);
    }
}

ToDoList::NotificationGuard::NotificationGuard(ToDoList &list, callback_t &&callback)
: _list(list), _callback(callback)
{}


ToDoList::NotificationGuard::~NotificationGuard() = default;

void ToDoList::NotificationGuard::schedule(ToDoList::id_t id)
{
    auto& item = _list.items.find(id)->second;
    _pending = std::make_unique<Job>([&item, id, this]() {
        _callback(item->_message);
        _list.popTask(id);
    });
    _pending->runAt(item->_timePoint);
}
