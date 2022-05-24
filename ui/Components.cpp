//
// Created by sungaoran on 2022/5/4.
//

#include "Components.h"
#include "tools.h"

namespace UI {
    BasicText::BasicText(lv_obj_t *parent, const lv_font_t *font, lv_coord_t width, int fade_out_t, int fade_in_t)
            : m_fade_in_t(fade_in_t),
              m_fade_out_t(fade_out_t) {
        label = lv_label_create(parent);
        label_set_style(label, font);
        lv_label_set_recolor(label, true);
        lv_obj_set_width(label, width);
        lv_label_set_text(label, "");
    }

    void BasicText::update() const {
        lv_label_set_text(label, text.c_str());
    }

    void BasicText::fade_in() const {
        auto a = anim_create(label, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, m_fade_in_t);
        lv_anim_start(&a);
    }

    static void fade_cb(struct _lv_anim_t *anim) {
        auto *ui = static_cast<BasicText *>(anim->user_data);
        ui->update();
        ui->fade_in();
    }

    void BasicText::update(const char *content, bool anim_on, bool force, uint32_t delay) {
        if (text.empty() || text != content || force) {
            text = content;
            if (anim_on) {
                auto a = anim_create(label, anim_fade, LV_OPA_COVER, LV_OPA_TRANSP, m_fade_out_t, delay, 0, 0, fade_cb,
                                     this);
                lv_anim_start(&a);
            } else {
                update();
            }
        }
    }
}