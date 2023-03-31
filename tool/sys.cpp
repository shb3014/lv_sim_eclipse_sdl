//
// Created by sungaoran on 2022/4/23.
//

#include "sys.h"
#include "sstream"
#include "iomanip"
#include <chrono>

const char *month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

std::string double_to_string(double value, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

unsigned long  millis()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    return value.count();
}

std::string get_mon_str(int mon) {
    return month[mon];
}

std::string get_mday_str(int mday) {
    int tail_str_index = mday % 10;
    const char *tail_str;
    if (tail_str_index == 1) {
        tail_str = "st";
    } else if (tail_str_index == 2) {
        tail_str = "nd";
    } else if (tail_str_index == 3) {
        tail_str = "rd";
    } else {
        tail_str = "th";
    }
    return std::to_string(mday) + tail_str;
}

void path_convert(std::string &path)
{
    size_t pos = 0;
    while ((pos = path.find('/', pos)) != std::string::npos) {
        path.replace(pos, 1, "\\");
        pos += 2;                          // Move past the replaced "\\" character
    }
}
