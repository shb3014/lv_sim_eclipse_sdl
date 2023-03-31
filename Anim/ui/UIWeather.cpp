//
// Created by sungaoran on 2022/1/18.
//

#include "UIWeather.h"
#include "tools.h"
#include "lv_conf.h"

#include "Anim/lang/Lang.h"
#include <math.h>

namespace UI {
    UIWeather::UIWeather() : Base() {
        auto lay_left = lv_obj_create(m_scr);
        auto lay_right = lv_obj_create(m_scr);
        lv_obj_remove_style_all(lay_left);
        lv_obj_remove_style_all(lay_right);
        lv_obj_set_size(lay_left, 140, 240);
        lv_obj_set_pos(lay_left, 0, 0);
        lv_obj_set_size(lay_right, 140, 240);
        lv_obj_set_pos(lay_right, 140, 0);

        city_label = lv_label_create(m_scr);

        Lang::Language::instance().lang_set_style_text_font(city_label,
                                                            {.zh = Lang::mi_light_font_36,
                                                             .en = Lang::ba_font_40,
                                                             .jp = Lang::jp_font_36});

        lv_label_set_text(city_label, "--");
        lv_obj_set_pos(city_label, 18, 30);

        weather_anim = lv_canvas_create(lay_left);
        anim_canvas_reset_asset();
        lv_obj_align(weather_anim, LV_ALIGN_CENTER, 0, -5);

        current_temp_label = lv_label_create(lay_right);
        Lang::Language::instance().lang_set_style_text_font(current_temp_label,
                                                            {.zh = Lang::mi_light_font_109,
                                                             .en = Lang::ba_font_120,
                                                             .jp = Lang::jp_font_120});
        minus_line = lv_line_create(m_scr);
        lv_obj_set_style_line_color(minus_line, lv_color_white(), 0);
        lv_line_set_points(minus_line, minus_line_points, 2);
        lv_obj_set_style_line_width(minus_line, 10, 0);


        weather_label = lv_label_create(lay_left);
        Lang::Language::instance().lang_set_style_text_font(weather_label,
                                                            {.zh = Lang::mi_light_font_24,
                                                             .en = Lang::ba_font_16,
                                                             .jp = Lang::jp_font_24},
                                                            lv_color_white(), LV_TEXT_ALIGN_RIGHT);

        temp_range_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(temp_range_label,
                                                            {.zh = Lang::mi_light_font_24,
                                                             .en = Lang::ba_font_30,
                                                             .jp = Lang::jp_font_24});

        temp_unit_label = lv_label_create(m_scr);
        Lang::Language::instance().lang_set_style_text_font(temp_unit_label,
                                                            {.zh = Lang::mi_light_font_24,
                                                             .en = Lang::ba_font_40,
                                                             .jp = Lang::jp_font_24});
    }

    static void set_width(void *var, int32_t v) {
        lv_obj_set_width((lv_obj_t *) var, v);
    }

    static void set_height(void *var, int32_t v) {
        lv_obj_set_height((lv_obj_t *) var, v);
    }

    static double C2F(double C) {
        return C = (C * 9 / 5) + 32;
    }

    static std::string get_degree_string(double T) {
        double temp = T;
        if (false) {
            temp = C2F(temp);
        }
        return std::to_string(abs((int) round(temp)));
    }

    static std::string get_temp_abs() {
        return get_degree_string(25);
    }

    static std::string get_temp_max() {
        return get_degree_string(32);
    }

    static std::string get_temp_min() {
        return get_degree_string(20);
    }

    static std::string get_temp_unit() {
        if (false) {
            return "℉";
        } else {
            return "℃";
        }
    }

    void UIWeather::update() {
        //const weather_t &weather = Sys::get_geo_info().weather;
        anim_canvas_bind_asset(weather_anim, "weather/rain.b");

        //lv_label_set_text(city_label, Sys::get_geo_info().location.city.c_str());

        lv_label_set_text(city_label, "outside");

        lv_label_set_text(current_temp_label, get_temp_abs().c_str());
        lv_obj_set_style_text_align(current_temp_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(current_temp_label, LV_ALIGN_CENTER, 10, -10);

        lv_label_set_text(weather_label, "clear");
        lv_obj_align(weather_label, LV_ALIGN_CENTER, 0, 60);

        std::string range = get_temp_min() + "/" + get_temp_max() + "°";
        lv_label_set_text(temp_range_label, range.c_str());
        lv_obj_align_to(temp_range_label, current_temp_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        lv_label_set_text(temp_unit_label, get_temp_unit().c_str());
        lv_obj_align_to(temp_unit_label, current_temp_label, LV_ALIGN_OUT_RIGHT_TOP, -15, -25);


        if (false) {
            lv_obj_align_to(minus_line, current_temp_label, LV_ALIGN_OUT_LEFT_MID, 10, 0);
            lv_obj_clear_flag(minus_line, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(minus_line, LV_OBJ_FLAG_HIDDEN);
        }

    }

    void UIWeather::routine() {
        anim_canvas_update(weather_anim);
    }

    void UIWeather::start_routine() {
        Base::start_routine();
        update();
    }
}