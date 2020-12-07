#pragma once
#include <map>
#include <memory>
#include <thread>
#include <future>
#include "ToDoItem.h"
#include "Job.h"

class ToDoList
{
private:
    using id_t = time_t;

public:
    using container = std::map<id_t, std::unique_ptr<ToDoItem>>;
    using iterator = container::const_iterator;
    using value_type = container::mapped_type;
    using callback_t = std::function<void(const std::string&)>;

    void addItem(value_type&&);
    void setCallback(callback_t &&callback);
    iterator begin();
    iterator end();

private:
    struct NotificationGuard
    {
        friend class ToDoList;
        NotificationGuard(ToDoList& list, callback_t &&callback);
        ~NotificationGuard();

        void schedule(id_t);
        ToDoList& _list;
        callback_t _callback;
        std::unique_ptr<Job> _pending;
    };

    container items;
    std::unique_ptr<NotificationGuard> _guard;
    std::mutex _items_lock;

    void popTask(id_t id);
};

