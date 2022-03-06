//
// Created by sungaoran on 2022/2/27.
//

#include "UIActionBox.h"

#include <utility>
#include "tools.h"

void UIActionBox::show() {
    m_title_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(m_title_label, &ba_40, 0);
    lv_obj_set_style_text_color(m_title_label, lv_color_white(), 0);
    lv_obj_set_width(m_title_label, 200);

    m_desc_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(m_desc_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_desc_label, lv_color_white(), 0);
    lv_obj_set_width(m_desc_label, 200);

    m_left_button = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(m_left_button, &ba_30, 0);
    lv_obj_set_style_text_color(m_left_button, lv_color_make(52, 192, 0), 0);

    m_right_button = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(m_right_button, &ba_30, 0);
    lv_obj_set_style_text_color(m_right_button, lv_color_white(), 0);

    m_touch_left_label = lv_label_create(lv_scr_act());
    lv_label_set_text(m_touch_left_label, "touch left");
    lv_obj_set_style_text_font(m_touch_left_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_touch_left_label, lv_color_white(), 0);


    m_touch_right_label = lv_label_create(lv_scr_act());
    lv_label_set_text(m_touch_right_label, "touch right");
    lv_obj_set_style_text_font(m_touch_right_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_touch_right_label, lv_color_white(), 0);

    lv_anim_t anim_left = anim_create(m_touch_left_label, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 2000, 0, 2500, 1200,
                                      nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&anim_left);

    lv_anim_t anim_right = anim_create(m_touch_right_label, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 2000, 0, 2500, 1200,
                                       nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&anim_right);

    m_counting_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(m_counting_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_counting_label, lv_color_white(), 0);
    lv_obj_add_flag(m_counting_label, LV_OBJ_FLAG_HIDDEN);

    m_counting_arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(m_counting_arc, 50, 50);
    lv_obj_set_style_arc_width(m_counting_arc, 2, 0);
    lv_obj_set_style_arc_width(m_counting_arc, 2, LV_PART_INDICATOR);
    lv_arc_set_rotation(m_counting_arc, 0);
    lv_arc_set_value(m_counting_arc, 100);
    lv_arc_set_bg_angles(m_counting_arc, 0, 360);
    lv_obj_set_style_arc_color(m_counting_arc, lv_color_black(), 0);
    lv_obj_set_style_arc_color(m_counting_arc, lv_color_make(200, 200, 200), LV_PART_INDICATOR);
    lv_obj_remove_style(m_counting_arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(m_counting_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(m_counting_arc, LV_OBJ_FLAG_HIDDEN);

    UIBase::show();
}

void
UIActionBox::update(const char *title, const char *desc, const char *left, const char *right, action_cb_t left_cb,
                    action_cb_t right_cb, int counting_max) {
    lv_label_set_text(m_title_label, title);
    lv_obj_set_style_text_align(m_title_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(m_title_label, LV_ALIGN_CENTER, 0, -60);

    lv_label_set_text(m_desc_label, desc);
    lv_obj_set_style_text_align(m_desc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(m_desc_label, m_title_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);


    lv_label_set_text(m_left_button, left);
    lv_obj_set_style_text_align(m_left_button, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(m_left_button, m_desc_label, LV_ALIGN_OUT_BOTTOM_MID, -80, 20);

    lv_label_set_text(m_right_button, right);
    lv_obj_set_style_text_align(m_right_button, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(m_right_button, m_desc_label, LV_ALIGN_OUT_BOTTOM_MID, 80, 20);

    lv_obj_set_style_text_align(m_touch_left_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(m_touch_left_label, m_left_button, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    lv_obj_set_style_text_align(m_touch_right_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(m_touch_right_label, m_right_button, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    lv_obj_align_to(m_counting_arc, m_desc_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    if (counting_max > 0) {
        m_counting_max = counting_max;
    }

    m_left_cb = std::move(left_cb);
    m_right_cb = std::move(right_cb);
}

void UIActionBox::routine() {
    if (m_counting_max > 0) {
        int time_left = m_counting_max - m_counting_t;
        if (time_left >= 0) {
            std::string time_left_str = std::to_string(time_left) + "s";
            lv_label_set_text(m_counting_label, time_left_str.c_str());
            lv_obj_align_to(m_counting_label, m_counting_arc, LV_ALIGN_CENTER, 0, 0);
            lv_arc_set_value(m_counting_arc, time_left * 100 / m_counting_max);
            m_counting_t++;
        } else {
            if (m_right_cb) {
                m_right_cb();
                m_counting_max = 0;
            }
        }
        lv_obj_clear_flag(m_counting_arc, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(m_counting_label, LV_OBJ_FLAG_HIDDEN);
    }
    UIBase::routine();

}
