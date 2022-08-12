//
// Created by sungaoran on 2022/1/18.
//

#include "UIWeather.h"
#include "tools.h"
#include "lv_conf.h"
//#include "behaviortree_cpp_v3/utils/make_unique.hpp"
//#include "Network/IvyNet.h"

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

        lv_obj_t *outside_label = lv_label_create(m_scr);
        lv_obj_set_style_text_font(outside_label, &ba_40, 0);
        lv_obj_set_style_text_color(outside_label, lv_color_white(), 0);
        lv_label_set_text(outside_label, "Outside");
        lv_obj_set_pos(outside_label, 18, 30);

        weather_anim = lv_canvas_create(lay_left);
        anim_canvas_reset_asset();
        lv_obj_align(weather_anim, LV_ALIGN_CENTER, 0, -5);

        current_temp_label = lv_label_create(lay_right);
        lv_obj_set_style_text_font(current_temp_label, &ba_120, 0);
        lv_obj_set_style_text_color(current_temp_label, lv_color_white(), 0);

        minus_line = lv_line_create(m_scr);
        lv_obj_set_style_line_color(minus_line, lv_color_white(), 0);
        lv_line_set_points(minus_line, minus_line_points, 2);
        lv_obj_set_style_line_width(minus_line, 10, 0);


        weather_label = lv_label_create(lay_left);
        lv_obj_set_style_text_font(weather_label, &ba_16, 0);
        lv_obj_set_style_text_align(weather_label, LV_TEXT_ALIGN_RIGHT, 0);
        lv_obj_set_style_text_color(weather_label, lv_color_white(), 0);

        temp_range_label = lv_label_create(m_scr);
        lv_obj_set_style_text_font(temp_range_label, &ba_30, 0);
        lv_obj_set_style_text_align(temp_range_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_style_text_color(temp_range_label, lv_color_white(), 0);


        temp_unit_label = lv_label_create(m_scr);
        lv_obj_set_style_text_font(temp_unit_label, &ba_40, 0);
        lv_obj_set_style_text_color(temp_unit_label, lv_color_white(), 0);
        lv_obj_set_style_text_align(temp_unit_label, LV_TEXT_ALIGN_CENTER, 0);

//    const weather_t &weather = IvyNet::instance().get_geo_info().weather;
//    update_info(weather.brief.c_str(), weather.brief.c_str(), weather.temp, weather.min, weather.max);
//    update_info(weather.brief.c_str(), "weather", weather.temp, weather.min, weather.max);/* fixme */
}

    static void set_width(void *var, int32_t v) {
        lv_obj_set_width((lv_obj_t *) var, v);
    }

    static void set_height(void *var, int32_t v) {
        lv_obj_set_height((lv_obj_t *) var, v);
    }

    int n = -40;

    void test_cb(struct _lv_timer_t *timer) {
        if (n < 10) {
            n++;
        } else {
            n = -10;
        }
        auto ui = (UIWeather *) timer->user_data;
        ui->update_info("partly sunny", "too_much_light.a", n, 20, 35);
    }

    void
    UIWeather::update_info(const char *weather, const char *asset_name, int current_degree, int degree_min,
                           int degree_max) {
        anim_canvas_bind_asset(weather_anim, asset_name);

        lv_label_set_text(current_temp_label, std::to_string(abs(current_degree)).c_str());
        lv_obj_set_style_text_align(current_temp_label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(current_temp_label, LV_ALIGN_CENTER, 10, -10);

        lv_label_set_text(weather_label, weather);
        lv_obj_align(weather_label, LV_ALIGN_CENTER, 0, 60);

        std::string range = std::to_string(degree_min) + "/" + std::to_string(degree_max) + "°";
        lv_label_set_text(temp_range_label, range.c_str());
        lv_obj_align_to(temp_range_label, current_temp_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        lv_label_set_text(temp_unit_label, "°C");
        lv_obj_align_to(temp_unit_label, current_temp_label, LV_ALIGN_OUT_RIGHT_TOP, -15, -25);


        if (current_degree >= 0) {
            lv_obj_add_flag(minus_line, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_align_to(minus_line, current_temp_label, LV_ALIGN_OUT_LEFT_MID, 10, 0);
            lv_obj_clear_flag(minus_line, LV_OBJ_FLAG_HIDDEN);
        }

    }

    void UIWeather::routine() {
        anim_canvas_update(weather_anim);
    }
}