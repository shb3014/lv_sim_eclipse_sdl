//
// Created by Huwensong on 2022/10/20.
//

#include "TextDriver.h"

#include <fstream>
#include "lib/nlohmann/Njson.hpp"
#include "Anim/ui/tools.h"
#include "utils/log.h"

extern std::string text_json_str;

namespace Lang {
    const std::array<std::string, lang_max> language = {
            "zh",
            "en",
            "jp",
    };

    Text &Text::instance() {
        static std::shared_ptr<Text> instance(new Text());
        return *instance;
    }

    void Text::load_text(const std::string &path, lang_t lang) {
        std::ifstream in_file;

        in_file.open(path);
        if (!in_file.fail())
        {
            nlohmann::json js;
            in_file >> js;
            in_file.close();

            for (const auto &it: js.items()) {
                nlohmann::json js_text = it.value();
                m_text_content.insert(std::make_pair(js_text["index"].get<uint32_t>(),
                                                     js_text["content"][language.at(lang)].get<std::string>()));
            }
            log_i("loaded text for %s", language.at(lang).c_str());
        } else                                                                                    // 加载默认文本
        {
            log_i("load default text!");
            nlohmann::json js;
            try {
                js = nlohmann::json::parse(text_json_str);
            }
            catch (std::exception &e) {
                log_e("load json text failed!");
            }


            for (const auto &it: js.items()) {
                nlohmann::json js_text = it.value();
                m_text_content.insert(std::make_pair(js_text["index"].get<uint32_t>(),
                                                     js_text["content"]["en"].get<std::string>()));
            }
        }
    }

    std::string Text::get_text(uint32_t index) {
        std::string ret = "null string";
        auto content = m_text_content.find(index);
        if (content != m_text_content.end())
            ret = content->second;
        return ret;
    }

    void Text::clean_text() {
        m_text_content.clear();
    }

    std::string Text::option_string(const char *str, int option) {
        try {
            nlohmann::json js = nlohmann::json::parse(str);
            for (auto &opt: js) {
                if (opt.is_array() && opt[0] == option) {
                    return opt[1];
                }
            }
            return js[0];
        } catch (...) {
            return "";
        }
    }

    std::string Text::color_in_str(UI::palette_t palette, std::string str) {
        //#adlsa#
        //#00ff00 adlsaj#

        std::string init_str = str;
        std::string color_limit = "#";
        size_t first_pos = init_str.find_first_of(color_limit);
        if (first_pos == init_str.npos) {
            std::string ret = "num in str not found";
            return ret;
        }
        init_str.insert(first_pos + 1, (get_palette_hex(palette) + " "));

        log_d("color str = %s", init_str.c_str());
        return init_str;
    }
}



