//
// Created by Gordon on 2021/8/13.
//

#include "Base.h"

namespace UI {
    Base::Base() {
        m_scr = lv_obj_create(NULL);
        lv_obj_set_style_bg_color(m_scr, lv_color_black(), 0);

        /* init routable indicator */
        for (auto &m_routable_indicator: m_routable_indicators) {
            m_routable_indicator = lv_led_create(m_scr);
            lv_obj_add_flag(m_routable_indicator, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_size(m_routable_indicator, 7, 7);
            lv_obj_set_style_shadow_opa(m_routable_indicator, LV_OPA_TRANSP, 0);
            lv_led_set_color(m_routable_indicator, lv_color_make(245, 203, 38));
        }
        lv_obj_align(m_routable_indicators[0], LV_ALIGN_LEFT_MID, 10, 0);
        lv_obj_align(m_routable_indicators[1], LV_ALIGN_RIGHT_MID, -10, 0);
    }

    Base::~Base() {
        lv_obj_del(m_scr);
    }

    void Base::clear() {

    }

    void Base::routine() {

    }

    void Base::input_cb(input_t input) {

    }

    void Base::set_routable_indicator_visible(bool visible, routable_indicator_part part) {
        std::vector<lv_obj_t *> indicators;
        if (part == left || part == all) {
            indicators.push_back(m_routable_indicators[0]);
        }
        if (part == right || part == all) {
            indicators.push_back(m_routable_indicators[1]);
        }
        for (auto &m_routable_indicator: indicators) {
            if (visible) {
                lv_obj_clear_flag(m_routable_indicator, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_add_flag(m_routable_indicator, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}