//
// Created by sungaoran on 2022/1/19.
//

#ifndef LVGL_UITIME_H
#define LVGL_UITIME_H

#include "UIBase.h"
class UITime  :public UIBase{
public:
    void show() override;

    void routine() override;

    void update_info(const char *time, const char* day, const char* date, const char* weather);

private:
    lv_obj_t *weather_anim;
    lv_obj_t *time_label;
    lv_obj_t *day_label;
    lv_obj_t *date_label;
    lv_obj_t *sep_line;
    lv_point_t sep_line_points[2] = {{0, 0},
                                       {0, 80}};
};


#endif //LVGL_UITIME_H
