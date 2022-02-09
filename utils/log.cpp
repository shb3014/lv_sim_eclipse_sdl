//
// Created by sungaoran on 2022/1/18.
//

#include "log.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstdarg>
#include <ctime>
#include "chrono"

const char *pathToFileName(const char *path) {
    size_t i = 0;
    size_t pos = 0;
    char *p = (char *) path;
    while (*p) {
        i++;
        if (*p == '/' || *p == '\\') {
            pos = i;
        }
        p++;
    }
    return path + pos;
}

int log_printf(const char *format, ...) {
    static char loc_buf[64];
    char *temp = loc_buf;
    int len;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    len = vsnprintf(NULL, 0, format, arg);
    va_end(copy);
    if (len >= sizeof(loc_buf)) {
        temp = (char *) malloc(len + 1);
        if (temp == NULL) {
            return 0;
        }
    }

    vsnprintf(temp, len + 1, format, arg);
    printf("%s", temp);

    va_end(arg);
    if (len >= sizeof(loc_buf)) {
        free(temp);
    }
    return len;
}

std::string GetTimeAsString(std::string formatString, time_t theTime)
{
    struct tm *timeinfo;
    timeinfo = localtime( &theTime);

    formatString += '\a'; //force at least one character in the result
    std::string buffer;
    buffer.resize(formatString.size());
    int len = strftime(&buffer[0], buffer.size(), formatString.c_str(), timeinfo);
    while (len == 0) {
        buffer.resize(buffer.size()*2);
        len = strftime(&buffer[0], buffer.size(), formatString.c_str(), timeinfo);
    }
    buffer.resize(len-1); //remove that trailing '\a'
    return buffer;
}

std::string get_ctime_now() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//    return GetTimeAsString("%F %T", now);
    return strtok(ctime(&now), "\n");
}