#include <chrono>
#include <iostream>
#include "TimeParser.h"
#include "ToDoItem.h"
#include "ToDoList.h"

inline void handle_new_task(ToDoList& list) {
    std::string title, raw_time;
    ItemBuilder builder;

    std::cout << "Title: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, title);
    builder.setMessage(title);

    std::cout << "When to remind you? : ";
    getline(std::cin, raw_time);

    if (TimeParser::parse(raw_time, builder) == TimeParser::unrecognized) {
        std::cout << "Unrecognized date format\n";
        return;
    }

    list.addItem(builder.build());
}

static std::mutex out_mutex;

int main()
{
    constexpr const char* help =
            "Type one of the following commands to proceed:\n"
            "- new : add new task\n"
            "- quit : exit the program\n"
            "- help : see this message again";
    constexpr const char* prompt = "> ";

    std::cout << "Welcome!\n";
    std::cout << "Tasks for today:\n"; // TODO
    std::cout << help << std::endl;

    ToDoList list;
    list.setCallback([](const std::string& s) {
        std::unique_lock<std::mutex> lock(out_mutex);
        std::cout << "\nNotification!\n";
        std::cout << s << '\n';
        std::cout << prompt;
        std::cout.flush();
    });

    for (;;) {
        if (!out_mutex.try_lock()) continue;

        std::cout << prompt;
        std::string input;
        std::cout.flush();
        out_mutex.unlock();
        std::cin >> input;

        std::unique_lock<std::mutex> lock(out_mutex);
        if (std::cin.eof() || input == "quit")
            break;

        if (input == "new")
            handle_new_task(list);
        else if (input == "help")
            std::cout << help << std::endl;
        else {
            std::cout << "Sorry, command '" << input << "' was not recognized\n";
        }
    }
}
