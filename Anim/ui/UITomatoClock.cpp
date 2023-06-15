//
// Created by Huwensong on 2023/6/8.
//

#include "UITomatoClock.h"
#include "tools.h"

LV_IMG_DECLARE(TomatoFruit)
LV_IMG_DECLARE(TomatoLeaf)
LV_IMG_DECLARE(TomatoTotal)
LV_IMG_DECLARE(TomatoSum)

#define TIME_BASE      60

#define CLOCK_MINUTES  25
#define CLOCK_SECONDS  0

#define GROWTH_PERIOD  ((CLOCK_MINUTES * TIME_BASE + CLOCK_SECONDS) * 1000)

#define STAGE_GROWTH_PERIOD_MINUTES 5
#define STAGE_GROWTH_PERIOD_SECONDS 0

#define TIMER_PERIOD   1000

namespace UI
{
    UITomatoClock::UITomatoClock() : Base(),
    m_img_tomato_fruit(lv_img_create(m_scr)),
    m_img_tomato_leaf(lv_img_create(m_scr)),
    time_label(lv_label_create(m_scr)),
    m_top_text(m_scr),
    m_bottom_text(m_scr)
    {
        lv_img_set_src(m_img_tomato_fruit,&TomatoFruit);
        lv_obj_align(m_img_tomato_fruit, LV_ALIGN_CENTER, 0, 0);

        lv_img_set_src(m_img_tomato_leaf,&TomatoLeaf);
        lv_obj_align_to(m_img_tomato_leaf,m_img_tomato_fruit,LV_ALIGN_TOP_RIGHT,0,0);


        lv_obj_set_width(time_label,160);
        lv_obj_align_to(time_label,m_img_tomato_fruit,LV_ALIGN_CENTER,0,-10);
        lv_obj_set_style_text_font(time_label,&lv_font_montserrat_48,0);
        lv_obj_set_style_text_color(time_label,lv_color_white(),0);
        lv_obj_set_style_text_align(time_label,LV_TEXT_ALIGN_CENTER,0);

        lv_obj_align(m_top_text.label,LV_ALIGN_TOP_MID,10,0);
        lv_obj_set_style_text_font(m_top_text.label,&lv_font_montserrat_16,0);
        lv_obj_set_style_text_color(m_top_text.label,lv_color_white(),0);
        lv_obj_set_style_text_align(m_top_text.label,LV_TEXT_ALIGN_CENTER,0);

        lv_obj_align(m_bottom_text.label,LV_ALIGN_BOTTOM_MID,0,-5);
        lv_obj_set_style_text_font(m_bottom_text.label,&lv_font_montserrat_14,0);
        lv_obj_set_style_text_color(m_bottom_text.label,lv_color_white(),0);
        lv_obj_set_style_text_align(m_bottom_text.label,LV_TEXT_ALIGN_CENTER,0);

        set_routable_indicator_visible(all);

        m_clock_seconds = CLOCK_MINUTES * TIME_BASE + CLOCK_SECONDS;
    }

    UITomatoClock::~UITomatoClock()
    {

    }

    void UITomatoClock::clear()
    {
        if (m_timer != nullptr)
            lv_timer_del(m_timer);
        Base::clear();
    }

    void UITomatoClock::routine()
    {
        update_time();
        update_text();

        if (m_tomato_is_ripened)
        {
            m_tomato_ripen_num ++;
            m_tomato_is_ripened = false;
        }
    }

    void UITomatoClock::input_cb(input_t input)
    {
        if (input == UI_INPUT_LEFT)
        {

        }
        else if (input == UI_INPUT_RIGHT)
        {
            if (m_clock_status == clock_status_init || m_clock_status == clock_status_stop)
                clock_start();
            else if (m_clock_status ==  clock_status_start)
                clock_stop();
        }
        else
        {
            ;//
        }
    }

    void UITomatoClock::front_input_cb(bool touch)
    {

    }

    void UITomatoClock::start_routine()
    {
        init_color_list();

        uint32_t anim_time = (STAGE_GROWTH_PERIOD_MINUTES * TIME_BASE + STAGE_GROWTH_PERIOD_SECONDS) * 1000;

        color_anim_create(LV_OPA_COVER,LV_OPA_TRANSP,anim_time);

        m_timer = lv_timer_create(timer_wrapper,TIMER_PERIOD, this);
        lv_timer_ready(m_timer);
    }

    void UITomatoClock::init_color_list()
    {
        m_color_list = {
                {lv_color_make(128,224,45)},
                {lv_color_make(179,221,47)},
                {lv_color_make(237,231,38)},
                {lv_color_make(255,206,51)},
                {lv_color_make(255,104,51)},
                {lv_color_make(255,51,51)},
        };
    }

    void UITomatoClock::color_anim_create(int32_t value_start,int32_t value_end,uint32_t ms)
    {
        lv_anim_init(&m_color_anim);
        lv_anim_set_var(&m_color_anim, this);
        lv_anim_set_exec_cb(&m_color_anim, color_grad_wrapper);
        lv_anim_set_values(&m_color_anim, value_start, value_end);
        lv_anim_set_time(&m_color_anim, ms);

        lv_anim_set_path_cb(&m_color_anim,lv_anim_path_linear);

        lv_anim_set_user_data(&m_color_anim, this);

        lv_anim_set_repeat_count(&m_color_anim, m_color_list.size() - 1);

    }

    void UITomatoClock::color_grad(uint32_t value)
    {
        lv_color_t start_color;
        lv_color_t target_color;

        m_color_anim_p = lv_anim_get(this,color_grad_wrapper);

        if (m_color_anim_p)
        {
            printf("repeat count = %d\n",m_color_anim_p->repeat_cnt);

            m_tomato_stage = m_color_list.size() - 1 - m_color_anim_p->repeat_cnt;


            start_color = m_color_list.at(m_tomato_stage);
            target_color = m_color_list.at(m_tomato_stage + 1);

            lv_color_t grad_color = lv_color_mix(start_color,target_color,value);

            lv_obj_set_style_img_recolor(m_img_tomato_fruit, grad_color, 0);
            lv_obj_set_style_img_recolor_opa(m_img_tomato_fruit, LV_OPA_COVER, 0);
        }
    }

    void UITomatoClock::color_grad_wrapper(void *var,int32_t value)
    {
        static_cast<UITomatoClock *>(var)->color_grad(value);
    }

    void UITomatoClock::timer_cb()
    {
        if (m_clock_status == clock_status_start)
        {
            if (m_clock_seconds == 0)
            {
                m_clock_status = clock_status_stop;
                m_tomato_is_ripened = true;
            }

            m_clock_seconds --;
        }
    }

    void UITomatoClock::timer_wrapper(lv_timer_t *timer)
    {
        auto instance = static_cast<UITomatoClock *>(timer->user_data);

        instance->timer_cb();
    }

    void UITomatoClock::update_time()
    {
        char time_str[6];

        sprintf(time_str,"%02d:%02d",m_clock_seconds / TIME_BASE,m_clock_seconds % TIME_BASE);

        lv_label_set_text(time_label,time_str);
    }

    void UITomatoClock::update_text()
    {
        switch (m_clock_status)
        {
            case clock_status_init:
                m_top_text.update("When you're ready, focus!");
                m_bottom_text.update("Touch right to start tomato clock.\nTouch left to check number of tomatoes");
                break;
            case clock_status_start:
                update_stage_text();
                m_bottom_text.update("Touch right to stop tomato clock(Better Not).");
                break;
            case clock_status_stop:
                m_top_text.update("One tomato clock finished, you are great!");
                m_bottom_text.update("Touch right to take 5 minutes break.\nTouch left to skip the break");
                break;
            default:
                break;
        }
    }

    void UITomatoClock::update_stage_text()
    {
        switch (m_tomato_stage)
        {
            case 1:
                m_top_text.update("Stay Focus!");
                break;
            case 2:
                m_top_text.update("Focus for 10 minutes. Keep it up!");
                break;
            case 3:
                m_top_text.update("Less than 10 minutes. Come on!");
                break;
            case 4:
                m_top_text.update("For the last five minutes, don't let up!");
                break;
            default:
                break;
        }
    }

    void UITomatoClock::clock_start()
    {
        m_clock_status = clock_status_start;

        lv_anim_start(&m_color_anim);

        set_routable_indicator_visible(false,left);
    }

    void UITomatoClock::clock_stop()
    {
        m_clock_status = clock_status_stop;
        m_clock_seconds = CLOCK_MINUTES * TIME_BASE + CLOCK_SECONDS;
    }




    UITomatoStatistics::UITomatoStatistics() : Base(),
    m_lay_total(lv_obj_create(m_scr)),
    m_img_tomato_total(lv_img_create(m_lay_total)),
    m_img_tomato_sum(lv_img_create(m_scr)),
    m_label_tomato_num(lv_label_create(m_img_tomato_sum)),
    m_label_top_text(lv_label_create(m_lay_total)),
    m_label_bottom_text(lv_label_create(m_scr))
    {
        lv_obj_set_size(m_lay_total, 185, 35);
        lv_obj_set_style_bg_opa(m_lay_total, LV_OPA_20, 0);
        lv_obj_clear_flag(m_lay_total, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_radius(m_lay_total, 10, 0);
        lv_obj_align(m_lay_total, LV_ALIGN_TOP_MID, 0, 20);

        lv_img_set_src(m_img_tomato_total,&TomatoTotal);
        lv_obj_align(m_img_tomato_total, LV_ALIGN_CENTER, 20, 0);

        lv_img_set_src(m_img_tomato_sum,&TomatoSum);
        lv_obj_align(m_img_tomato_sum, LV_ALIGN_CENTER, 0, 10);

        lv_obj_align(m_label_tomato_num, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_text_font(m_label_tomato_num,&lv_font_montserrat_48,0);
        lv_obj_set_style_text_color(m_label_tomato_num,lv_color_white(),0);
        lv_obj_set_style_text_align(m_label_tomato_num,LV_TEXT_ALIGN_CENTER,0);

        lv_obj_align(m_label_top_text, LV_ALIGN_LEFT_MID, 0, 0);
        lv_obj_set_style_text_font(m_label_top_text,&lv_font_montserrat_12,0);
        lv_obj_set_style_text_color(m_label_top_text,lv_color_white(),0);
        lv_obj_set_style_text_align(m_label_top_text,LV_TEXT_ALIGN_CENTER,0);

        lv_obj_align(m_label_bottom_text, LV_ALIGN_BOTTOM_MID, 0, -10);
        lv_obj_set_style_text_font(m_label_bottom_text,&lv_font_montserrat_24,0);
        lv_obj_set_style_text_color(m_label_bottom_text,lv_color_white(),0);
        lv_obj_set_style_text_align(m_label_bottom_text,LV_TEXT_ALIGN_CENTER,0);

        set_routable_indicator_visible(all);


    }

    void UITomatoStatistics::start_routine()
    {
        m_tomato_sum = 0;  // 获取番茄总数

        m_tomato_total = 0;  // 获取历史番茄总数

        m_tomato_total += m_tomato_sum;

        // 番茄总数存入文件。
        update_text();
    }

    void UITomatoStatistics::update_text()
    {
        std::string top_text = "My Tomato :              x " + std::to_string(m_tomato_total);

        std::string tomato_num = std::to_string(m_tomato_sum);

        lv_label_set_text(m_label_top_text,top_text.c_str());

        lv_label_set_text(m_label_tomato_num,tomato_num.c_str());

        lv_label_set_text(m_label_bottom_text,"Today Tomato");
    }


}

