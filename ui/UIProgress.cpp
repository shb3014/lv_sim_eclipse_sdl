//
// Created by sungaoran on 2021/11/16.
//

#include "UIProgress.h"
#include "string"

namespace UI {
    UIProgress::UIProgress() : Base() {
        static lv_style_t style_bg;
        static lv_style_t style_indic;

        lv_style_init(&style_bg);
        lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_GREEN));
        lv_style_set_border_width(&style_bg, 2);
        lv_style_set_pad_all(&style_bg, 6); /*To make the indicator smaller*/
        lv_style_set_radius(&style_bg, 6);
        lv_style_set_anim_time(&style_bg, 1000);

        lv_style_init(&style_indic);
        lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
        lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_GREEN));
        lv_style_set_radius(&style_indic, 3);

        m_bar = lv_bar_create(m_scr);
        lv_obj_remove_style_all(m_bar);  /*To have a clean start*/
        lv_obj_add_style(m_bar, &style_bg, 0);
        lv_obj_add_style(m_bar, &style_indic, LV_PART_INDICATOR);

        lv_obj_set_size(m_bar, 200, 20);
        lv_obj_center(m_bar);

        m_title_label = lv_label_create(m_scr);
        lv_obj_set_style_text_font(m_title_label, &ba_30, 0);
        lv_obj_set_style_text_color(m_title_label, lv_color_white(), 0);
        lv_obj_set_style_text_align(m_title_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_title_label, m_bar, LV_ALIGN_OUT_TOP_MID, 0, -10);

        m_status_label = lv_label_create(m_scr);
        lv_obj_set_style_text_font(m_status_label, &ba_16, 0);
        lv_obj_set_style_text_color(m_status_label, lv_color_white(), 0);
        lv_obj_set_style_text_align(m_status_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_status_label, m_bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }

    void UIProgress::set_title(const char *value) {
        lv_label_set_text(m_title_label, value);
        lv_obj_align_to(m_title_label, m_bar, LV_ALIGN_OUT_TOP_MID, 0, -10);
    }

    void UIProgress::set_status(const char *value) {
        lv_label_set_text(m_status_label, value);
        lv_obj_align_to(m_status_label, m_bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }

    void UIProgress::set_progress(uint8_t progress) {
        lv_bar_set_value(m_bar, progress, LV_ANIM_ON);
    }

    void UIProgress::update(const char *title, const char *status, uint8_t progress) {
        if (std::string(title) != lv_label_get_text(m_title_label)) {
            /* update title */
            lv_label_set_text(m_title_label, title);
            lv_obj_align_to(m_title_label, m_bar, LV_ALIGN_OUT_TOP_MID, 0, -10);

        }
        if (std::string(status) != lv_label_get_text(m_status_label)) {
            /* update status */
            lv_label_set_text(m_status_label, status);
            lv_obj_align_to(m_status_label, m_bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        }
        lv_bar_set_value(m_bar, progress, LV_ANIM_ON);
    }
}