//
// Created by sungaoran on 2022/1/20.
//

#ifndef LVGL_UIDATE_H
#define LVGL_UIDATE_H

#include "Base.h"
namespace UI {
    class UIDate : public Base {
    public:
        UIDate();

        void start_routine() override;

        index_t get_index() override {
            return UI_DATE;
        }

        void calendar_show_cb();

        void label_hide_cb();

        void clear() override;

    private:
        lv_obj_t *calendar;
        lv_obj_t *mask;
        lv_obj_t *init_label;
        lv_obj_t *line;
        lv_point_t line_points[2] = {{0,   0},
                                     {260, 0}};
        lv_timer_t *timer = nullptr;
    };

}
#endif //LVGL_UIDATE_H
