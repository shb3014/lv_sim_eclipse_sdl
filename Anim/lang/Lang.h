//
// Created by Gordon on 2022/11/29.
//

#ifndef PLANTSIO_IVY_LANG_H
#define PLANTSIO_IVY_LANG_H

#include "Anim/lang/managed/LanguageDefine.h"
#include "Anim/lang/managed/LangEnum.h"
#include "Anim/lang/driver/TextDriver.h"
#include "Anim/lang/driver/LanguageDriver.h"

#define LANG_COLOR(color, text) Lang::Text::instance().color_in_str(color, text)

#define LANG(text) Lang::Text::instance().get_text(text).c_str()

#define LANG_OPTION(text, option) Lang::Text::option_string(Lang::Text::instance().get_text(text).c_str(),option)

template<typename T>
std::string toString(T value) {
    return std::to_string(value);
}

template<>
std::string toString<std::string>(std::string value);


/**
 * format a string by replacing {} with values
 * @param str
 * @param values
 * @return
 */
template<typename T>
std::string format_string(const char *str, std::vector<T> values) {
    try {
        std::string ret = str;
        std::string::size_type n = 0;
        std::string placeholder = "{}";
        int replace_index = 0;
        while ((n = ret.find(placeholder, n)) != std::string::npos) {
            std::string replace_str;
            if (replace_index < values.size()) {
                replace_str = toString<T>(values[replace_index++]);
            } else {
                replace_str = " ";
            }
            ret.replace(n, placeholder.size(), replace_str);
            n += replace_str.size();
        }
        return ret;
    } catch (...) {
        return str;
    }
}


template<typename T>
std::string LANG_FORMAT(uint32_t index, std::vector<T> values) {
    return format_string<T>(Lang::Text::instance().get_text(index).c_str(), values);
}

#endif //PLANTSIO_IVY_LANG_H
