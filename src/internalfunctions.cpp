#include "internalfunctions.h"
#include <chrono>

std::string INTERNALFUNCTIONS::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct std::tm *now_tm = std::localtime(&now_c);

    //формат год-месяц-день 00:00:00
    std::string year = std::to_string((now_tm->tm_year + 1900));

    std::string mon = std::to_string((now_tm->tm_mon + 1));
    if (mon.length() == 1) { mon = "0" + mon; }

    std::string day = std::to_string(now_tm->tm_mday);
    if (day.length() == 1) { day = "0" + day; }

    std::string hour = std::to_string(now_tm->tm_hour);
    if (hour.length() == 1) { hour = "0" + hour; }

    std::string min = std::to_string(now_tm->tm_min);
    if (min.length() == 1) { min = "0" + min; }

    std::string sec = std::to_string(now_tm->tm_sec);
    if (sec.length() == 1) { sec = "0" + sec; }

    return year + "-" + mon + "-" + day + " " + hour + ":" + min + ":" + sec;
}

std::string INTERNALFUNCTIONS::getUserStatus(int status)
{

    switch (status) {
        case 1: {
        return "ACTIVE";
            break;

        }
        case 2: {
            return "NOT_ACTIVE";
            break;
        }
        case 3: {
            return "BANNED";
            break;
        }
    }
}
