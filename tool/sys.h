//
// Created by sungaoran on 2022/4/23.
//

#ifndef LVGL_SYS_H
#define LVGL_SYS_H

#include <string>

std::string double_to_string(double value, int precision);

unsigned long  millis();

std::string get_mon_str(int mon);

std::string get_mday_str(int mday);

void path_convert(std::string &path);

#endif //LVGL_SYS_H
