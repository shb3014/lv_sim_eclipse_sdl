//
// Created by sungaoran on 2022/1/18.
//

#ifndef UI_SANDBOX_UIWEATHER_H
#define UI_SANDBOX_UIWEATHER_H

#include "UIBase.h"

class UIWeather : public UIBase {
public:
    void show() override;

    void routine() override;

    void update_info(const char *weather, const char *asset_name, int current_degree, int degree_min, int degree_max);

private:
    lv_obj_t *weather_anim;
    lv_obj_t *weather_label;
    lv_obj_t *current_temp_label;
    lv_obj_t *temp_range_label;
    lv_obj_t *temp_unit_label;
    lv_obj_t *minus_line;
    lv_point_t minus_line_points[2] = {{0, 0},
                                       {20, 0}};
};


#endif //UI_SANDBOX_UIWEATHER_H
