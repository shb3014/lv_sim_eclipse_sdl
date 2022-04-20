//
// Created by Gordon on 2021/8/13.
//

#include "Base.h"

namespace UI {
    Base::Base() {
        m_scr = lv_obj_create(NULL);
        lv_obj_set_style_bg_color(m_scr, lv_color_black(), 0);
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
}