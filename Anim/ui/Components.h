//
// Created by sungaoran on 2022/5/4.
//

#ifndef LVGL_COMPONENTS_H
#define LVGL_COMPONENTS_H

#include "lvgl/lvgl.h"
#include "string"

#include "Anim/lang/Lang.h"

namespace UI {
    class BasicText {
    public:
        explicit BasicText(lv_obj_t *parent, lv_coord_t width = 300, int fade_out_t = 1200,
                           int fade_in_t = 1000);

        void set_text_font(Lang::lang_desc lang);

        void update() const;

        void update(const char *content, bool anim_on = true, bool force = false, uint32_t delay = 0);

        void fade_in() const;

        lv_obj_t *label;
        std::string text;

    private:
        int m_fade_out_t;
        int m_fade_in_t;
    };

    class SelectButton {
    public:
        SelectButton(lv_obj_t *parent, const char* btn_text,const char* desc_text,lv_color_t color=lv_color_white());

        void start_anim();

        void align(lv_coord_t x, lv_coord_t y);

    private:
        lv_obj_t *m_button;
        lv_obj_t *m_desc;
        lv_anim_t m_anim={};
    };


}

#endif //LVGL_COMPONENTS_H
