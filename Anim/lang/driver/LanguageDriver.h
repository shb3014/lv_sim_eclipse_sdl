//
// Created by Huwensong on 2022/10/20.
//

#ifndef MI_PLANTS_IVY_LANGUAGEDRIVER_H
#define MI_PLANTS_IVY_LANGUAGEDRIVER_H

#include <string>
#include <unordered_map>

#include "Anim/ui/Base.h"
#include "Anim/lang/managed/LanguageDefine.h"
#include "lvgl/lvgl.h"

namespace Lang {
    typedef struct {
        font_t size;
        std::string path;
    } font_path_t;

    void set_language(lang_t lang);

    class Language {

    public:

        Language(const Language &) = delete;

        Language(Language &&) = delete;

        Language &operator=(const Language &) = delete;

        Language &operator=(Language &&) = delete;

        static Language &instance();

    public:
        Language();

        lang_t get_language() const {
            return m_lang;
        }

        void lang_set_style_text_font(lv_obj_t *label, lang_desc lang,
                                      lv_color_t color = lv_color_white(),
                                      lv_text_align_t align = LV_TEXT_ALIGN_CENTER);

        void lang_set_style_text_font_selector(lv_obj_t *label, lang_desc lang,
                                                         lv_style_selector_t selector);

    private:
        /**
         * load language according to:
         * 1. User setting
         * 2. Code availability -- existence in lang map
         * 3. Resource availability -- font binary existence in storage
         */
        bool load_user_language();

        const lv_font_t *get_font(font_t size);

        static const lv_font_t *get_default_font(font_t size);

        void lang_set_style_text_font(lv_obj_t *label, lang_t lang, font_t size,
                                      lv_color_t color = lv_color_white(),
                                      lv_text_align_t align = LV_TEXT_ALIGN_CENTER);

        static std::string get_root_filepath();

    private:
        lang_t m_lang = en;

        lang_t m_last_language = en;

        std::unordered_map<font_t, lv_font_t *> m_font_map;

    };
}


#endif //MI_PLANTS_IVY_LANGUAGEDRIVER_H
