#include "TimeParser.h"
#include <regex>
#include <iomanip>
#include <iostream>

TimeParser::status TimeParser::parse(const std::string &entry, ItemBuilder &builder)
{
    static std::regex periodic(R"(every\s+(\d+)\s+(minute|hour|day|week|month)[s]?)");
    std::smatch matches;
    if (std::regex_search(entry, matches, periodic)) {
        auto q = std::stol(matches[1]);
        auto unit = stringToPeriod(matches[2]);
        builder.setPeriod(q, unit);
        std::cout << "Task is going to be repeated every " << matches[1] << " " << matches[2] << '\n';
    }

    auto& time = matches.empty() ? entry : matches.prefix().str();
    std::istringstream time_stream(time);
    std::tm parsed {};
    time_stream >> std::get_time(&parsed, one_time_fmt);
    if (!time_stream)
        return unrecognized;

    std::cout << std::put_time(&parsed, "%c %T") << std::endl;
    auto t_point = std::chrono::system_clock::from_time_t(std::mktime(&parsed));
    builder.setTime(t_point);
    return ok;
}

NotificationPeriod TimeParser::stringToPeriod(const std::string &repr)
{
    if (repr == "minute")
        return NotificationPeriod::minute;
    if (repr == "hour")
        return NotificationPeriod::hour;
    if (repr == "day")
        return NotificationPeriod::day;
    if (repr == "week")
        return NotificationPeriod::week;
    if (repr == "month")
        return NotificationPeriod::month;
    return NotificationPeriod::once;
}
