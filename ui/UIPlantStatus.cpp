//
// Created by Gordon on 2022/4/15.
//

#include "UIPlantStatus.h"

StatusCard::StatusCard(lv_obj_t *parent, const char *name, const char *unit) {
    m_card = lv_obj_create(parent);
    lv_obj_set_size(m_card,100,110);
    lv_obj_set_style_bg_opa(m_card,LV_OPA_TRANSP,0);
    lv_obj_set_scrollbar_mode(m_card,LV_SCROLLBAR_MODE_OFF );

    m_value_label = lv_label_create(m_card);
    update_value_label("0");

    m_name_label = lv_label_create(m_card);
    lv_label_set_text(m_name_label, name);
    lv_obj_align(m_name_label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_font(m_name_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_name_label, lv_color_white(),0);

    m_unit_label = lv_label_create(m_card);
    lv_label_set_text(m_unit_label, unit);
    lv_obj_align_to(m_unit_label,m_name_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_set_style_text_font(m_unit_label, &ba_16, 0);
    lv_obj_set_style_text_color(m_unit_label, lv_color_white(),0);
}

void StatusCard::update_value_label(const char *value_str) {
    /* todo should adjust font size according to value string length */
    lv_label_set_text(m_value_label, value_str);
    lv_obj_set_style_text_font(m_value_label, &ba_40, 0);
    lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_text_color(m_value_label, lv_color_white(),0);
}

UIPlantStatus::UIPlantStatus()
        : UIBase(),
          card_temp(m_scr, "temp", "°C"),
          card_humidity(m_scr, "humidity", "%"),
          card_soil(m_scr, "soil", "%"),
          card_water(m_scr, "water", "mL"),
          card_battery(m_scr, "battery", "%"),
          card_light(m_scr, "light", "lx") {
    lv_obj_set_flex_flow(m_scr,LV_FLEX_FLOW_ROW_WRAP);

}