//
// Created by Huwensong on 2023/6/8.
//

#ifndef LVGL_UITOMATOCLOCK_H
#define LVGL_UITOMATOCLOCK_H

#include "lvgl/lvgl.h"

#include "Base.h"
#include "Components.h"

typedef enum ClockStatus
{
    clock_status_init,
    clock_status_start,
    clock_status_stop,
}clock_status_t;

namespace UI
{
    class UITomatoClock : public Base
    {
    public:
        UITomatoClock();
        ~UITomatoClock();

    public:
        void clear() override;

        /* called every frame */
        void routine() override;

        /* bound to touch events */
        void input_cb(input_t input) override;

        void front_input_cb(bool touch) override;

    protected:
        void start_routine() override;

    private:
        void init_color_list();

        void color_anim_create(int32_t value_start,int32_t value_end,uint32_t ms);

        void color_grad(uint32_t value);

        static void color_grad_wrapper(void *var,int32_t value);

        void timer_cb();

        static void timer_wrapper(lv_timer_t *timer);

        void update_time();

        void update_text();

        void update_stage_text();

        void clock_start();

        void clock_stop();


    private:
        lv_obj_t *m_img_tomato_fruit;

        lv_obj_t *m_img_tomato_leaf;

        lv_obj_t *time_label;

        lv_anim_t m_color_anim;

        lv_anim_t *m_color_anim_p = nullptr;

        lv_timer_t *m_timer = nullptr;

        std::vector<lv_color_t> m_color_list;

        BasicText m_top_text;

        BasicText m_bottom_text;

        uint8_t m_tomato_stage = 0;

        clock_status_t m_clock_status = clock_status_init;

        uint32_t m_clock_seconds = 0;

        bool m_tomato_is_ripened = false;

        uint32_t m_tomato_ripen_num = 0;


    };

    class UITomatoStatistics : public Base
    {
    public:
        UITomatoStatistics();

    public:
        void start_routine() override;

    private:
        void update_text();

    private:
        lv_obj_t *m_lay_total;

        lv_obj_t *m_img_tomato_total;

        lv_obj_t *m_img_tomato_sum;

        lv_obj_t *m_label_tomato_num;

        lv_obj_t *m_label_top_text;

        lv_obj_t *m_label_bottom_text;

        uint32_t m_tomato_total = 0;

        uint32_t m_tomato_sum = 0;


    };
}


#endif //LVGL_UITOMATOCLOCK_H
