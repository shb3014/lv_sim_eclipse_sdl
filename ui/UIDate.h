//
// Created by sungaoran on 2022/1/20.
//

#ifndef LVGL_UIDATE_H
#define LVGL_UIDATE_H

#include "UIBase.h"

class UIDate : public UIBase {
public:
    void show() override;

    void calendar_show_cb();

    void label_hide_cb();

private:
    lv_obj_t *calendar;
    lv_obj_t *mask;
    lv_obj_t *init_label;
    lv_obj_t *line;
    lv_point_t line_points[2] = {{0,   0},
                                 {260, 0}};
    lv_timer_t *timer;
};


#endif //LVGL_UIDATE_H
