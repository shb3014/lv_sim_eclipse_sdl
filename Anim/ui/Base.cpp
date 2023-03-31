//
// Created by Gordon on 2021/8/13.
//

#include "Base.h"
#include "memory"

namespace UI {
    Base::Base() : m_scr(lv_obj_create(NULL)) {
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

        lv_obj_add_event_cb(m_scr, mouse_cb, LV_EVENT_CLICKED, this);
    }

    Base::~Base() {
        del();
    }

    void Base::clear() {
        m_cleared = true;
    }

    void Base::routine() {

    }

    void Base::input_cb(input_t input) {

    }

    void Base::front_input_cb(bool touch)
    {

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

    void Base::mouse_cb(lv_event_t *event)
    {
        lv_indev_t *indev = lv_indev_get_act();
        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if (indev_type == LV_INDEV_TYPE_POINTER)
        {
            lv_point_t point;
            lv_indev_get_point(indev, &point);
            if (point.x < 160)
            {
                static_cast<Base *>(event->user_data)->input_cb(UI_INPUT_LEFT);
            }
            else if (point.x > 160)
            {
                static_cast<Base *>(event->user_data)->input_cb(UI_INPUT_RIGHT);
            }
            else if (point.y > 12)
            {
                static_cast<Base *>(event->user_data)->front_input_cb(true);
            }
            else
            {
                ; //
            }
        }
    }
}