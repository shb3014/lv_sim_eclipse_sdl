//
// Created by sungaoran on 2022/5/4.
//

#include "Components.h"

#include "tools.h"

namespace UI {
    BasicText::BasicText(lv_obj_t *parent, lv_coord_t width, int fade_out_t, int fade_in_t)
            : m_fade_in_t(fade_in_t),
              m_fade_out_t(fade_out_t) {
        label = lv_label_create(parent);
        lv_label_set_recolor(label, true);
        lv_obj_set_width(label, width);
        lv_label_set_text(label, "");
    }

    void BasicText::set_text_font(Lang::lang_desc lang)
    {
            Lang::Language::instance().lang_set_style_text_font(label, lang);
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

    SelectButton::SelectButton(lv_obj_t *parent, const char *btn_text, const char *desc_text, lv_color_t color)
            : m_desc(lv_label_create(parent)),
              m_button(lv_label_create(parent)) {
        Lang::Language::instance().lang_set_style_text_font(m_button,
                                                            {.zh = Lang::mi_light_font_30,
                                                             .en = Lang::ba_font_30,
                                                             .jp = Lang::jp_font_30});

        Lang::Language::instance().lang_set_style_text_font(m_desc,
                                                            {.zh = Lang::mi_light_font_16,
                                                             .en = Lang::ba_font_16,
                                                             .jp = Lang::jp_font_16});
        lv_label_set_text(m_button, btn_text);
        lv_label_set_text(m_desc, desc_text);
        m_anim = anim_create(m_desc, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 2000, 0, 2500,
                             1200, nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);

    }

    void SelectButton::start_anim() {
        lv_anim_start(&m_anim);
    }

    void SelectButton::align(lv_coord_t x, lv_coord_t y) {
        lv_obj_align(m_button, LV_ALIGN_CENTER, x, y);
        lv_obj_align_to(m_desc, m_button, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    }
}