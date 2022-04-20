//
// Created by sungaoran on 2021/11/16.
//

#include "UIDoubleProgress.h"
#include "string"
#include "tools.h"
namespace UI {
    UIDoubleProgress::UIDoubleProgress() : UI::Base() {
        style_bg = bar_get_default_style_bg();
        style_indic = bar_get_default_style_indic();

        m_bar_1 = lv_bar_create(m_scr);
        lv_obj_remove_style_all(m_bar_1);  /*To have a clean start*/
        lv_obj_add_style(m_bar_1, &style_bg, 0);
        lv_obj_add_style(m_bar_1, &style_indic, LV_PART_INDICATOR);

        m_bar_2 = lv_bar_create(m_scr);
        lv_obj_remove_style_all(m_bar_2);  /*To have a clean start*/
        lv_obj_add_style(m_bar_2, &style_bg, 0);
        lv_obj_add_style(m_bar_2, &style_indic, LV_PART_INDICATOR);

        lv_obj_set_size(m_bar_1, 200, 20);
        lv_obj_align(m_bar_1, LV_ALIGN_CENTER, 0, -20);

        lv_obj_set_size(m_bar_2, 200, 20);
        lv_obj_align_to(m_bar_2, m_bar_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);

        m_title_label = lv_label_create(m_scr);
        lv_obj_set_style_text_font(m_title_label, &ba_30, 0);
        lv_obj_set_style_text_color(m_title_label, lv_color_white(), 0);
        lv_obj_set_style_text_align(m_title_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_title_label, m_bar_2, LV_ALIGN_OUT_TOP_MID, 0, -20);

        m_status_label_1 = lv_label_create(m_scr);
        lv_obj_set_style_text_font(m_status_label_1, &ba_16, 0);
        lv_obj_set_style_text_color(m_status_label_1, lv_color_white(), 0);
        lv_obj_set_style_text_align(m_status_label_1, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_status_label_1, m_bar_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        lv_obj_set_width(m_status_label_1, 300);

        m_status_label_2 = lv_label_create(m_scr);
        lv_obj_set_style_text_font(m_status_label_2, &ba_16, 0);
        lv_obj_set_style_text_color(m_status_label_2, lv_color_white(), 0);
        lv_obj_set_style_text_align(m_status_label_2, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_status_label_2, m_bar_2, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }


    void UIDoubleProgress::update(const char *title, const char *status_1, uint8_t progress_1, const char *status_2,
                                  uint8_t progress_2) {
        if (std::string(title) != lv_label_get_text(m_title_label)) {
            /* update title */
            lv_label_set_text(m_title_label, title);
            lv_obj_align_to(m_title_label, m_bar_1, LV_ALIGN_OUT_TOP_MID, 0, -20);

        }
        update_progress_1(status_1, progress_1);
        update_progress_2(status_2, progress_2);
    }

    void UIDoubleProgress::update_progress_1(const char *status_1, uint8_t progress_1) {
        if (std::string(status_1) != lv_label_get_text(m_status_label_1)) {
            /* update status */
            lv_label_set_text(m_status_label_1, status_1);
            lv_obj_align_to(m_status_label_1, m_bar_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        }
        lv_bar_set_value(m_bar_1, progress_1, LV_ANIM_OFF);
    }

    void UIDoubleProgress::update_progress_2(const char *status_2, uint8_t progress_2) {
        if (std::string(status_2) != lv_label_get_text(m_status_label_2)) {
            /* update status */
            lv_label_set_text(m_status_label_2, status_2);
            lv_obj_align_to(m_status_label_2, m_bar_2, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        }
        lv_bar_set_value(m_bar_2, progress_2, LV_ANIM_OFF);
    }
}