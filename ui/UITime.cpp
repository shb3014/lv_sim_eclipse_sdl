//
// Created by sungaoran on 2022/1/19.
//

#include "UITime.h"
#include "tools.h"

int i = 20;
int j = 0;
int w_index = 0;
int m_index = 0;
int date_day = 1;
const char* week_day[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
const char* month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
static void test_cb(struct _lv_timer_t *timer) {
    auto ui = (UITime *) timer->user_data;
    if (++j>60){
        j=0;
        if (++i>23){
            i=0;
        }
    }
    if (++w_index>6){
        w_index = 0;
    }
    if (++m_index>11){
        m_index = 0;
    }
    if (++date_day>31){
        date_day = 1;
    }
    char time[6];
    char date[9];
    const char* th = "th";
    if(date_day==1){
        th = "st";
    }else if (date_day == 2){
        th = "nd";
    }else if (date_day == 3){
        th = "rd";
    }
    sprintf(time,"%02d:%02d",i,j);
    sprintf(date,"%d%s %s",date_day,th,month[m_index]);
    ui->update_info(time, week_day[w_index], date, "weather");
}

void UITime::update_info(const char *time, const char *day, const char *date, const char *weather) {
    anim_canvas_bind_asset(weather_anim, weather);

    lv_label_set_text(time_label, time);
    lv_obj_align(time_label,LV_ALIGN_CENTER,0,-50);

    lv_label_set_text(day_label, day);
    lv_obj_align(day_label,LV_ALIGN_BOTTOM_LEFT,35,-65);

    lv_label_set_text(date_label, date);
    lv_obj_align(date_label,LV_ALIGN_BOTTOM_LEFT,35,-28);
}

void UITime::show() {

    weather_anim = lv_canvas_create(lv_scr_act());
    anim_canvas_reset_asset();
    anim_canvas_bind_asset(weather_anim, "weather");
//    lv_obj_set_pos(weather_anim, 200, 120);

    time_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(time_label, &ba_120, 0);
    lv_obj_set_style_text_color(time_label, lv_color_white(), 0);

    day_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(day_label, &ba_30, 0);
    lv_obj_set_style_text_color(day_label, lv_color_white(), 0);

    date_label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(date_label, &ba_30, 0);
    lv_obj_set_width(date_label,140);
    lv_obj_set_style_text_color(date_label, lv_color_white(), 0);

    sep_line = lv_line_create(lv_scr_act());
    lv_obj_set_style_line_color(sep_line, lv_color_make(255,255,255), 0);
    lv_line_set_points(sep_line,sep_line_points,2);
    lv_obj_set_style_line_width(sep_line,1,0);
    lv_obj_set_pos(sep_line,180,135);
//    lv_obj_align_to(sep_line,weather_anim,LV_ALIGN_OUT_LEFT_MID,-15,2);

    lv_obj_align_to(weather_anim, sep_line, LV_ALIGN_OUT_RIGHT_MID, 20, -6);

//    lv_timer_create(test_cb, 1000, this);

    update_info("21:25", week_day[3], "23th Jan", "weather");

    UIBase::show();
}

void UITime::routine() {
    anim_canvas_update(weather_anim);
}

