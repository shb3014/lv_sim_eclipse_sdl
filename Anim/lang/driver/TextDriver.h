//
// Created by Huwensong on 2022/10/20.
//

#ifndef MI_PLANTS_IVY_TEXTDRIVER_H
#define MI_PLANTS_IVY_TEXTDRIVER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Anim/ui/tools.h"
#include "Anim/lang/managed/LanguageDefine.h"

namespace Lang {
    class Text {
    public:
        Text() = default;

    public:
        static Text &instance();

    public:
        void load_text(const std::string &path, lang_t lang);

        std::string get_text(uint32_t index);

        void clean_text();

        /**
         * Selects a string with the option. If no option is found, the first str will be used.
         * example:
         * const char *s = R"(["test", [0,"Toxicity"], [1, "non-toxic"], [2, "poisonous"]])";
         * @param str
         * @param option
         * @return
         */
        static std::string option_string(const char *str, int option);

        std::string color_in_str(UI::palette_t palette, std::string str);

    private:
        std::unordered_map<uint32_t, std::string> m_text_content;

    };
}


#endif //MI_PLANTS_IVY_TEXTDRIVER_H
