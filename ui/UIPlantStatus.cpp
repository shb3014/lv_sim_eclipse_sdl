//
// Created by Gordon on 2022/4/15.
//

#include "UIPlantStatus.h"

StatusCard::StatusCard(lv_obj_t *parent, const char *name, const char *unit) {
    m_card = lv_obj_create(parent);
    lv_obj_set_size(m_card, 100, 110);
    lv_obj_set_style_bg_opa(m_card, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(m_card, LV_OBJ_FLAG_SCROLLABLE);

    m_value_label = lv_label_create(m_card);
    update_value_label("0");

    m_name_label = lv_label_create(m_card);
    lv_label_set_text(m_name_label, name);
    lv_obj_align(m_name_label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_font(m_name_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_name_label, lv_color_white(), 0);

    m_unit_label = lv_label_create(m_card);
    lv_label_set_text(m_unit_label, unit);
    lv_obj_align_to(m_unit_label, m_name_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_set_style_text_font(m_unit_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_unit_label, lv_color_white(), 0);
}

void StatusCard::update_value_label(const char *value_str) {
    /* todo should adjust font size according to value string length */
    lv_label_set_text(m_value_label, value_str);
    lv_obj_set_style_text_font(m_value_label, &ba_40, 0);
    lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_text_color(m_value_label, lv_color_white(), 0);
}

UIPlantStatus::UIPlantStatus()
        : UIBase(),
          bubble(m_scr, 300,100,20, 10),
          card_temp(m_scr, "temp", "°C"),
          card_humidity(m_scr, "humidity", "%"),
          card_soil(m_scr, "soil", "%"),
          card_water(m_scr, "water", "mL"),
          card_battery(m_scr, "battery", "%"),
          card_light(m_scr, "light", "lx") {
    lv_obj_set_flex_flow(m_scr, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(m_scr, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

}

ChatBubble::ChatBubble(lv_obj_t *parent, int16_t bubble_w, int16_t bubble_h, int16_t pointer_w, int16_t pointer_h,
                       lv_color_t color)
        : m_pointer(parent, pointer_w, pointer_h),
          m_color(color) {
    m_card = lv_obj_create(parent);
    lv_obj_set_size(m_card, bubble_w, bubble_h);
    m_label = lv_label_create(m_card);
    update_pointer_location(20);
}

void ChatBubble::update_pointer_location(int x) {
    lv_obj_align_to(m_pointer.body, m_card, LV_ALIGN_TOP_LEFT, x, 0);
}

BubblePointer::BubblePointer(lv_obj_t *parent, int16_t pointer_w, int16_t pointer_h)
        : left_points({{0,                         pointer_h},
                       {(int16_t) (pointer_w / 2), 0}}),
          right_points({{(int16_t) (pointer_w / 2), 0},
                        {pointer_w,                 pointer_h}}),
          bottom_points({{0,         pointer_h},
                         {pointer_w, pointer_h}}) {
    body = lv_obj_create(parent);
    lv_obj_remove_style_all(body);
    line_left = lv_line_create(body);
    line_right = lv_line_create(body);
    line_bottom = lv_line_create(body);
    lv_obj_set_size(body, pointer_w, pointer_h);
    lv_line_set_points(line_left, left_points.data(), 2);
    lv_line_set_points(line_right, right_points.data(), 2);
    lv_line_set_points(line_bottom, bottom_points.data(), 2);
}

void BubblePointer::update(lv_color_t color) {
    lv_obj_set_style_line_color(line_left, color, 0);
    lv_obj_set_style_line_color(line_right, color, 0);
    lv_obj_set_style_line_color(line_bottom, lv_color_black(), 0);
}
