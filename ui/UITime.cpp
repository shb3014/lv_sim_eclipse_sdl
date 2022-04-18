//
// Created by sungaoran on 2022/1/19.
//

#include "UITime.h"
#include "tools.h"
//#include "tool/sys.h"


UITime::UITime() : UIBase() {
    weather_anim = lv_canvas_create(m_scr);
//    lv_obj_set_pos(weather_anim, 200, 120);

    time_label = lv_label_create(m_scr);
    lv_obj_set_style_text_font(time_label, &ba_120, 0);
    lv_obj_set_style_text_color(time_label, lv_color_white(), 0);

    day_label = lv_label_create(m_scr);
    lv_obj_set_style_text_font(day_label, &ba_30, 0);
    lv_obj_set_style_text_color(day_label, lv_color_white(), 0);

    date_label = lv_label_create(m_scr);
    lv_obj_set_style_text_font(date_label, &ba_30, 0);
    lv_obj_set_style_text_color(date_label, lv_color_white(), 0);

    sep_line = lv_line_create(m_scr);
    lv_obj_set_style_line_color(sep_line, lv_color_make(255, 255, 255), 0);
    lv_line_set_points(sep_line, sep_line_points, 2);
    lv_obj_set_style_line_width(sep_line, 1, 0);
    lv_obj_set_pos(sep_line, 180, 135);

    update_info(true);
}

void UITime::start_routine() {
    anim_canvas_reset_asset();
    anim_canvas_bind_asset(weather_anim, "weather");

    lv_obj_align_to(weather_anim, sep_line, LV_ALIGN_OUT_RIGHT_MID, 20, -6);
    UIBase::start_routine();
}

void UITime::update_info(bool force) {
//    anim_canvas_bind_asset(weather_anim, weather);
    anim_canvas_bind_asset(weather_anim, "weather");

    time_t curtime;
    time(&curtime);
    tm *info = localtime(&curtime);

    /* "15:23", "FRI", "21st Jan", "weather" */

    if (force || last_tm.tm_hour != info->tm_hour || last_tm.tm_min != info->tm_min) {
        last_tm.tm_hour = info->tm_hour;
        last_tm.tm_min = info->tm_min;
        char time_str[6];
        sprintf(time_str, "%02d:%02d", info->tm_hour, info->tm_min);
        lv_label_set_text(time_label, time_str);
        lv_obj_align(time_label, LV_ALIGN_CENTER, 0, -50);
    }

    if (force || last_tm.tm_wday != info->tm_wday) {
        last_tm.tm_wday = info->tm_wday;
//        lv_label_set_text(day_label, get_wday_str(info->tm_wday).c_str());
        lv_obj_align(day_label, LV_ALIGN_BOTTOM_LEFT, 40, -65);
    }

    if (force || last_tm.tm_mday != info->tm_mday || last_tm.tm_mon != info->tm_mon) {
        last_tm.tm_mday = info->tm_mday;
        last_tm.tm_mon = info->tm_mon;
//        std::string date_str = get_mday_str(info->tm_mday).c_str() + std::string(" ") + get_mon_str(info->tm_mon);
//        lv_label_set_text(date_label, date_str.c_str());
        lv_obj_align(date_label, LV_ALIGN_BOTTOM_LEFT, 40, -20);
    }
}

void UITime::routine() {
    update_info();
    anim_canvas_update(weather_anim);
}

