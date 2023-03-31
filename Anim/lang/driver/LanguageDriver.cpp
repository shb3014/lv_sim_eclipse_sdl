//
// Created by Huwensong on 2022/10/20.
//

#include "LanguageDriver.h"

#include "TextDriver.h"
#include "../managed/LangMap.h"
#include "utils/log.h"
#include "tool/sys.h"

#define PATH_LANGUAGE                   "F:..\\Anim\\lang\\managed\\external"

namespace Lang {

    static lang_t language = en;

    void set_language(lang_t lang)
    {
        language = lang;
    }

    static std::string get_real_path(std::string &str)
    {
        uint8_t pos = str.find(":");

        if (pos != std::string::npos)
            return str.substr(pos + 1);
        else
            return std::string();
    }

    Language &Language::instance() {
        static std::shared_ptr<Language> instance(new Language());
        return *instance;
    }

    Language::Language() {
        if (!load_user_language()) {
            log_w("loading embedded language");
            /* no valid root path, load default text*/
            Text::instance().load_text("", m_lang);
        }
    }

    bool Language::load_user_language() {
        auto target_lang = language;
        std::unordered_map<lang_t, std::vector<font_path_t>> lang_map = LANG_MAP;

        auto it = lang_map.find(target_lang);
        if (it == lang_map.end()) {
            log_w("invalid language %d", target_lang);
            return false;
        }

        std::string root_path = get_root_filepath();
        if (root_path.empty()) {
            log_w("language %d resource not found", target_lang);
            return false;
        }

        for (auto &mapping: lang_map.find(target_lang)->second) {
#ifdef WIN32
            path_convert(mapping.path);
#endif
            std::string full_path = root_path + mapping.path;
            lv_font_t *font = lv_font_load(full_path.c_str());
            if (!font) {
                log_w("invalid language %d font at %s", target_lang, full_path.c_str());
                m_font_map.clear();
                return false;
            }
            m_font_map.insert(std::make_pair(mapping.size, font));
        }
        log_i("language %d successfully loaded", target_lang);
        m_lang = target_lang;

        /* load text with the acquired root path */
#ifdef WIN32
        std::string text_path = root_path + "\\text\\UIText.json";
#else
        std::string text_path = root_path + "/text/UIText.json";
#endif

        std::string real_text_path = get_real_path(text_path);
        log_d("text path = %s",real_text_path.c_str());
        Text::instance().load_text(real_text_path, m_lang);

        return true;
    }

    void Language::lang_set_style_text_font(lv_obj_t *label, lang_desc lang, lv_color_t color,
                                            lv_text_align_t align) {
        lang_set_style_text_font(label, en, lang.en, color, align);
        lang_set_style_text_font(label, zh, lang.zh, color, align);
        lang_set_style_text_font(label,jp,lang.jp,color,align);
    }

    const lv_font_t *Language::get_font(font_t size) {
        if (!m_font_map.empty()) {
            auto it = m_font_map.find(size);
            if (it != m_font_map.end() && it->second != nullptr) {
                return it->second;
            }
        }
        return get_default_font(size);
    }

    const lv_font_t *Language::get_default_font(font_t size) {
        const lv_font_t *font;
        switch (size) {
            case ba_font_16:
                font = &ba_16;
                break;
            case ba_font_30:
                font = &ba_30;
                break;
            case ba_font_40:
                font = &ba_40;
                break;
            case ba_font_120:
                font = &ba_120;
                break;
            default:
                font = &ba_16;
                break;
        }
        return font;
    }

    void Language::lang_set_style_text_font(lv_obj_t *label, lang_t lang, font_t size,
                                            lv_color_t color, lv_text_align_t align) {
        auto font = m_font_map.find(size);
        if (lang == m_lang) {
            lv_obj_set_style_text_font(label, get_font(size), 0);
            lv_obj_set_style_text_color(label, color, 0);
            lv_obj_set_style_text_align(label, align, 0);
        } else {
            return;  // 不是当前语言字体
        }

    }

    std::string Language::get_root_filepath() {
        return PATH_LANGUAGE;
    }
}
