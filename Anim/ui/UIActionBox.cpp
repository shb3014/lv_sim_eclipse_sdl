//
// Created by sungaoran on 2022/2/27.
//

#include "UIActionBox.h"

#include <utility>
#include "tools.h"

#include "Anim/lang/Lang.h"
#include "Anim/lang/Lang.h"
#include "utils/log.h"
#include "tool/sys.h"

namespace UI {
    UIActionBox::UIActionBox() : Base() {
        set_input_used(true);

        m_title_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_title_label,
                                                            {.zh = Lang::mi_light_font_30,
                                                             .en = Lang::ba_font_40,
                                                             .jp = Lang::jp_font_30});
        lv_obj_set_width(m_title_label, 240);

        m_desc_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_desc_label,
                                                            {.zh = Lang::mi_light_font_16,
                                                                    .en = Lang::ba_font_16,
                                                                    .jp = Lang::jp_font_16});
        lv_obj_set_width(m_desc_label, 240);

        m_left_button = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_left_button,
                                                            {.zh = Lang::mi_light_font_30,
                                                             .en = Lang::ba_font_30,
                                                             .jp = Lang::jp_font_30});

        m_right_button = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_right_button,
                                                            {.zh = Lang::mi_light_font_30,
                                                             .en = Lang::ba_font_30,
                                                             .jp = Lang::jp_font_30},
                                                            lv_color_make(52, 192, 0));

        m_touch_left_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_touch_left_label,
                                                            {.zh = Lang::mi_light_font_16,
                                                                    .en = Lang::ba_font_16,
                                                                    .jp = Lang::jp_font_16});
        lv_label_set_text(m_touch_left_label, Lang::Text::instance().get_text(Lang::ui_actionbox_touch_left).c_str());


        m_touch_right_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_touch_right_label,
                                                            {.zh = Lang::mi_light_font_16,
                                                                    .en = Lang::ba_font_16,
                                                                    .jp = Lang::jp_font_16});
        lv_label_set_text(m_touch_right_label, Lang::Text::instance().get_text(Lang::ui_actionbox_touch_right).c_str());

        m_counting_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(m_counting_label,
                                                            {.zh = Lang::mi_light_font_16,
                                                                    .en = Lang::ba_font_16,
                                                                    .jp = Lang::jp_font_16});
        lv_obj_add_flag(m_counting_label, LV_OBJ_FLAG_HIDDEN);

        m_counting_arc = lv_arc_create(m_scr);
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
    }

    void UIActionBox::start_routine() {
        lv_anim_t anim_left = anim_create(m_touch_left_label, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 2000, 0, 2500,
                                          1200,
                                          nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&anim_left);

        lv_anim_t anim_right = anim_create(m_touch_right_label, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 2000, 0, 2500,
                                           1200,
                                           nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&anim_right);
        Base::start_routine();
    }


    void
    UIActionBox::update(const char *title, const char *desc, const char *apply_desc, const char *cancel_desc,
                        action_cb_t apply_cb,
                        action_cb_t cancel_cb, action_cb_t final_cb, int counting_max) {
        lv_label_set_text(m_title_label, title);
        lv_obj_set_style_text_align(m_title_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(m_title_label, LV_ALIGN_CENTER, 0, -60);

        lv_label_set_text(m_desc_label, desc);
        lv_obj_set_style_text_align(m_desc_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_desc_label, m_title_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);


        lv_label_set_text(m_left_button, cancel_desc);
        lv_obj_set_style_text_align(m_left_button, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_left_button, m_desc_label, LV_ALIGN_OUT_BOTTOM_MID, -80, 20);

        lv_label_set_text(m_right_button, apply_desc);
        lv_obj_set_style_text_align(m_right_button, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_right_button, m_desc_label, LV_ALIGN_OUT_BOTTOM_MID, 80, 20);

        lv_obj_set_style_text_align(m_touch_left_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_touch_left_label, m_left_button, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

        lv_obj_set_style_text_align(m_touch_right_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align_to(m_touch_right_label, m_right_button, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

        lv_obj_align_to(m_counting_arc, m_desc_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

        if (counting_max > 0) {
            m_counting_max = counting_max;
            m_counting_timeout_t = millis() + counting_max * 1000;
        }

        m_apply_cb = std::move(apply_cb);
        m_cancel_cb = std::move(cancel_cb);
        m_final_cb = std::move(final_cb);
    }

    void UIActionBox::routine() {
        if (m_action == ACTION_WAITING) {
            if (m_counting_timeout_t > 0) {
                int time_left = m_counting_timeout_t - millis();
                if (time_left >= 0) {
                    uint32_t time_left_seconds = time_left / 1000;
                    std::string time_left_str = std::to_string(time_left_seconds) + "s";
                    if (time_left_str != lv_label_get_text(m_counting_label)) {
                        lv_label_set_text(m_counting_label, time_left_str.c_str());
                        lv_obj_align_to(m_counting_label, m_counting_arc, LV_ALIGN_CENTER, 0, 0);
//                    lv_arc_set_value(m_counting_arc, time_left_seconds * 100 / m_counting_max);
                        auto a = anim_create(m_counting_arc, (lv_anim_exec_xcb_t) lv_arc_set_value,
                                             lv_arc_get_value(m_counting_arc), time_left_seconds * 100 / m_counting_max,
                                             300);
                        lv_anim_start(&a);
                    }
                } else {
                    log_d("debug-ui action timeout");
                    if (m_cancel_cb) {
                        m_cancel_cb();
                        m_counting_timeout_t = 0;
                    }
                    if (m_final_cb) {
                        m_final_cb();
                        m_final_executed = true;
                    }
                }
                lv_obj_clear_flag(m_counting_arc, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(m_counting_label, LV_OBJ_FLAG_HIDDEN);
            }
        } else if (m_action == ACTION_APPLY) {
            m_action = ACTION_OVER;
            if (m_apply_cb) {
                m_apply_cb();
            }
            if (m_final_cb) {
                m_final_cb();
                m_final_executed = true;
            }
        } else if (m_action == ACTION_CANCEL) {
            m_action = ACTION_OVER;
            if (m_cancel_cb) {
                m_cancel_cb();
            }
            if (m_final_cb) {
                m_final_cb();
                m_final_executed = true;
            }
        }
        Base::routine();
    }

    void UIActionBox::input_cb(input_t input) {
        if (input == UI::UI_INPUT_LEFT) {
            set_action(ACTION_CANCEL);
        } else if (input == UI::UI_INPUT_RIGHT) {
            set_action(ACTION_APPLY);
        }
    }

    void UIActionBox::clear() {
        Base::clear();
        if (!m_final_executed && m_final_cb) {
            m_final_executed = true;
            m_final_cb();
        }
    }
}