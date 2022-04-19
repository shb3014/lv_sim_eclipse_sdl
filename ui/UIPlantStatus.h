//
// Created by Gordon on 2022/4/15.
//

#ifndef LVGL_UIPLANTSTATUS_H
#define LVGL_UIPLANTSTATUS_H

#include "UIBase.h"
#include "vector"
#include "string"

#define BUBBLE_HEIGHT       90
#define BUBBLE_POINTER_H    10
#define DEFAULT_PADDING     6
#define DEFAULT_CARD_H      (240-3*DEFAULT_PADDING)/2
#define DEFAULT_CARD_W      (320-4*DEFAULT_PADDING)/3

class StatusCard {
public:
    StatusCard(lv_obj_t *parent, const char *name, const char *unit);

    lv_obj_t *m_card;
private:
    void update_value_label(const char *value_str);


    lv_obj_t *m_value_label;
    lv_obj_t *m_name_label;
    lv_obj_t *m_unit_label;
};

class BubblePointer {
public:
    BubblePointer(lv_obj_t *parent, lv_coord_t pointer_w, lv_coord_t pointer_h, lv_coord_t line_w = 2);

    void update_color(lv_color_t color = lv_color_white());

    void set_direction(bool up);

    lv_obj_t *body;

private:
    lv_coord_t m_pointer_w;
    lv_coord_t m_pointer_h;
    lv_coord_t m_line_w;
    lv_obj_t *line_top;
    lv_obj_t *line_bottom;
    std::vector<lv_point_t> points_top;
    std::vector<lv_point_t> points_bottom;
};

class ChatBubble {
public:
    ChatBubble(lv_obj_t *parent, lv_coord_t bubble_w, lv_coord_t bubble_h, lv_coord_t pointer_w, lv_coord_t pointer_h);

    void update_pointer_location(int x, bool up);

    void update_color(lv_color_t color);

    void update_content(const char *content);

    void set_visible(bool show);

    lv_obj_t *m_space;
    bool visible = false;
private:
    BubblePointer m_pointer;
    lv_obj_t *m_card;
    lv_obj_t *m_label;
};

class UIPlantStatus : public UIBase {
public:
    UIPlantStatus();

    UI_index get_index() override {
        return UI_PLANT_STATUS;
    }

    void update_bubble_status(const char *content, lv_color_t color, lv_coord_t x, bool up, bool show);

    void hide_bubble_cb();

    void routine() override;

    void select_index(int index);

    void select_next();

    std::string get_content_by_index(int index);

    lv_color_t get_color_by_index(int index);

private:
    static lv_coord_t get_pointer_x_by_index(int index);
//    lv_coord_t col_dsc[4] = {100, 100, 100, LV_GRID_TEMPLATE_LAST};
//    lv_coord_t row_dsc[4] = {110, 110, 110, LV_GRID_TEMPLATE_LAST};
    lv_obj_t *top_area;
    ChatBubble bubble;
    lv_obj_t *bottom_area;
    StatusCard card_temp;
    StatusCard card_humidity;
    StatusCard card_soil;
    StatusCard card_water;
    StatusCard card_battery;
    StatusCard card_light;

    bool focus_top = true;
    int current_index = -1;
};


#endif //LVGL_UIPLANTSTATUS_H
