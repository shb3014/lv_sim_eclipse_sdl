//
// Created by Gordon on 2021/8/13.
//

#include "UIBase.h"

UIBase::UIBase() {
    m_scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(m_scr, lv_color_black(), 0);
}

UIBase::~UIBase() {
    lv_obj_del(m_scr);
}

void UIBase::clear() {

}

void UIBase::routine() {

}

void UIBase::input_cb(UI_INPUT input) {

}
