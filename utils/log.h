//
// Created by sungaoran on 2022/1/18.
//

#ifndef LVGL_LOG_H
#define LVGL_LOG_H

#include <cstdio>
#include <string>
std::string get_ctime_now();

const char *pathToFileName(const char *path);

#define LOG_FORMAT(letter, format)  "[" #letter " %s][%s:%u] " format "\r\n", get_ctime_now().c_str(), pathToFileName(__FILE__), __LINE__



int log_printf(const char *fmt, ...);

#define log_d(format, ...) log_printf(LOG_FORMAT(D, format), ##__VA_ARGS__)
#define log_i(format, ...) log_printf(LOG_FORMAT(I, format), ##__VA_ARGS__)
#define log_w(format, ...) log_printf(LOG_FORMAT(W, format), ##__VA_ARGS__)
#define log_e(format, ...) log_printf(LOG_FORMAT(E, format), ##__VA_ARGS__)

#endif //LVGL_LOG_H
