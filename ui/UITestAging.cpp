//
// Created by Gordon on 2022/11/9.
//

#include "UITestAging.h"
#include "tools.h"
#include "tool/sys.h"

namespace UI {
    UITestAging::UITestAging()
            : Base(),
              m_time_label(lv_label_create(m_scr)),
              m_test_anim(lv_canvas_create(m_scr)),
              m_charging_bar(lv_bar_create(m_scr)),
              m_charging_label(lv_label_create(m_scr)),
              m_timeout_label(lv_label_create(m_scr)) {

        label_set_style(m_time_label, &ba_40);

        anim_canvas_reset_asset();

        bar_set_default_style(m_charging_bar);
        lv_obj_set_size(m_charging_bar, 200, 20);

        label_set_style(m_charging_label, &ba_30);
        label_set_style(m_timeout_label, &ba_16);

    }

    void UITestAging::routine() {
        anim_canvas_update(m_test_anim);
    }

    void UITestAging::start_routine() {
        Base::start_routine();
        anim_canvas_bind_asset(m_test_anim, "weather/snow.b");
        update(0, 0, 0, "");
        lv_obj_align(m_test_anim, LV_ALIGN_CENTER, 0, -15);
        lv_obj_align_to(m_charging_bar, m_test_anim, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    }

    void
    UITestAging::update(uint32_t time, int progress, int timeout, const char *content, lv_color_t bck_color,
                        lv_color_t text_color) {
        uint32_t hour = time / 3600;
        uint32_t min = (time % 3600) / 60;
        uint32_t seconds = time % 60;
        std::string timer_str =
                std::to_string(hour) + "h " + std::to_string(min) + "m " + std::to_string(seconds) + "s ";
        lv_label_set_text(m_time_label, timer_str.c_str());
        lv_obj_align(m_time_label, LV_ALIGN_TOP_MID, -30, 10);

        lv_bar_set_value(m_charging_bar, progress, LV_ANIM_OFF);

        std::string con = std::to_string(progress) + "% | " + content;
        lv_label_set_text(m_charging_label, con.c_str());
        lv_obj_align_to(m_charging_label, m_charging_bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        lv_label_set_text(m_timeout_label, ("[" + std::to_string(timeout) + "s]").c_str());
        lv_obj_align_to(m_timeout_label, m_time_label, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

        lv_obj_set_style_bg_color(m_scr, bck_color, 0);
        lv_obj_set_style_text_color(m_time_label, text_color, 0);
        lv_obj_set_style_text_color(m_charging_label, text_color, 0);
        lv_obj_set_style_text_color(m_timeout_label, text_color, 0);
    }
}