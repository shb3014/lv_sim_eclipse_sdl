//
// Created by sungaoran on 2022/5/4.
//

#ifndef LVGL_COMPONENTS_H
#define LVGL_COMPONENTS_H

#include "lvgl/lvgl.h"
#include "string"

namespace UI {
    class BasicText {
    public:
        explicit BasicText(lv_obj_t *parent, const lv_font_t *font, lv_coord_t width = 280, int fade_out_t = 1200,
                           int fade_in_t = 1000);

        void update() const;

        void update(const char *content, bool anim_on = true);

        void fade_in() const;

        lv_obj_t *label;
        std::string text;

    private:
        int m_fade_out_t;
        int m_fade_in_t;
    };
}

#endif //LVGL_COMPONENTS_H
