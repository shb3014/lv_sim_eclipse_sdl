//
// Created by sungaoran on 2022/1/19.
//

#ifndef LVGL_UITIME_H
#define LVGL_UITIME_H

#include <ctime>
#include "Base.h"

namespace UI {
    class UITime : public Base {
    public:
        UITime();

        index_t get_index() override {
            return UI_TIME;
        }

        void start_routine() override;

        void routine() override;

        void update_info(bool force = false);

    private:
        lv_obj_t *weather_anim;
        lv_obj_t *time_label;
        lv_obj_t *day_label;
        lv_obj_t *date_label;
        lv_obj_t *sep_line;
        lv_point_t sep_line_points[2] = {{0, 0},
                                         {0, 80}};

        tm last_tm{};
    };
}

#endif //LVGL_UITIME_H
