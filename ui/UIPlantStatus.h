//
// Created by Gordon on 2022/4/15.
//

#ifndef LVGL_UIPLANTSTATUS_H
#define LVGL_UIPLANTSTATUS_H

#include "UIBase.h"
#include "vector"

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

class BubblePointer {
public:
    BubblePointer(lv_obj_t *parent, int16_t pointer_w, int16_t pointer_h);

    void update(lv_color_t color = lv_color_white());

    lv_obj_t *body;

private:
    lv_obj_t *line_left;
    lv_obj_t *line_right;
    lv_obj_t *line_bottom;
    std::vector<lv_point_t> left_points;
    std::vector<lv_point_t> right_points;
    std::vector<lv_point_t> bottom_points;
};

class ChatBubble {
public:
    ChatBubble(lv_obj_t *parent, int16_t bubble_w, int16_t bubble_h, int16_t pointer_w, int16_t pointer_h, lv_color_t color = lv_color_white());

    void update_pointer_location(int x);

private:
    BubblePointer m_pointer;
    lv_color_t m_color;
    lv_obj_t *m_card;
    lv_obj_t *m_label;
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
    ChatBubble bubble;
//    lv_obj_t *message_label;
};


#endif //LVGL_UIPLANTSTATUS_H
