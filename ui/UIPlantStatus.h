//
// Created by Gordon on 2022/4/15.
//

#ifndef LVGL_UIPLANTSTATUS_H
#define LVGL_UIPLANTSTATUS_H

#include "UIBase.h"

class StatusCard {
public:
    StatusCard(lv_obj_t *parent, const char *name, const char *unit);

private:
    void update_value_label(const char *value_str);

    lv_obj_t *m_card;
    lv_obj_t *m_value_label;
    lv_obj_t *m_name_label;
    lv_obj_t *m_unit_label;
};

class UIPlantStatus : public UIBase {
public:
    UIPlantStatus();

    UI_index get_index() override {
        return UI_PLANT_STATUS;
    }

private:
    StatusCard card_temp;
    StatusCard card_humidity;
    StatusCard card_soil;
    StatusCard card_water;
    StatusCard card_battery;
    StatusCard card_light;
//    lv_obj_t *message_label;
};


#endif //LVGL_UIPLANTSTATUS_H
