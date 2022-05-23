//
// Created by Gordon on 2022/5/23.
//

#include "UIFluidAssist.h"
#include "tools.h"

namespace UI {
    UIFluidAssist::UIFluidAssist(int tank_size)
            : UIFluid(tank_size),
              m_bar_label(lv_label_create(m_scr)),
              m_bar_top(lv_line_create(m_scr)),
              m_bar_bottom(lv_line_create(m_scr)),
              m_bar_middle(lv_line_create(m_scr)) {

        line_set_style(m_bar_top, FLUID_BAR_WIDTH, get_palette_rgb(palette_warning), true);
        line_set_style(m_bar_middle, FLUID_BAR_WIDTH, get_palette_rgb(palette_success), true);
        line_set_style(m_bar_bottom, FLUID_BAR_WIDTH, lv_color_make(61, 150, 165), true);/* fixme */
        label_set_style(m_bar_label, &lv_font_montserrat_12);
        lv_label_set_text_fmt(m_bar_label, "%s", LV_SYMBOL_PLAY);
        lv_obj_add_flag(m_bar_label, LV_OBJ_FLAG_HIDDEN);

        lv_coord_t x = (LV_HOR_RES - m_tank_size) / 2 - 10;
        m_assist_start_y = (LV_VER_RES - m_tank_size) / 2;
        m_bar_points[0] = {.x=x, .y=(lv_coord_t) (m_assist_start_y + 8)};
        m_bar_points[1] = {.x=x, .y=(lv_coord_t) (m_assist_top + m_assist_start_y)};
        m_bar_points[2] = {.x=x, .y=(lv_coord_t) (m_assist_bottom + m_assist_start_y)};
        m_bar_points[3] = {.x=x, .y=(lv_coord_t) (m_tank_size - 8 + m_assist_start_y)};
    }

    void UIFluidAssist::start_routine() {
        update_assist_bar();
#ifdef Ivy
        m_top_label.update(("Please add water to about " + std::to_string(Plant::get_target_water_volume()) +
                            "mL").c_str());
#endif
    }

    uint16_t UIFluidAssist::get_target_level() {
//        return Plant::get_target_water_volume();
        return 20;
    }

    uint16_t UIFluidAssist::get_target_range() {
//        return Plant::get_target_water_range();
        return 5;
    }

    void UIFluidAssist::update_assist_bar() {
        int target_level = get_target_level();
        int target_level_range = get_target_range();
        lv_coord_t target_y = m_tank_size - (double) target_level / WATER_TANK_VOLUME * m_tank_size;
        auto target_y_range = (lv_coord_t) ((double) target_level_range / WATER_TANK_VOLUME * m_tank_size);
        m_assist_top = target_y > target_y_range ? target_y - target_y_range : 0;
        m_assist_bottom = target_y + target_y_range < m_tank_size ? target_y + target_y_range : m_tank_size;

        m_bar_points[1].y = (lv_coord_t) (m_assist_top + m_assist_start_y);
        m_bar_points[2].y = (lv_coord_t) (m_assist_bottom + m_assist_start_y);
        lv_line_set_points(m_bar_top, m_bar_points, 2);
        lv_line_set_points(m_bar_bottom, m_bar_points + 2, 2);
        lv_line_set_points(m_bar_middle, m_bar_points + 1, 2);
    }

    void UIFluidAssist::render_wave() {
//        if (m_current_y>m_assist_bottom){
//            m_front_wave_color = get_palette_rgb(palette_notice);
//        }else if (m_current_y<m_assist_top){
//            m_front_wave_color = get_palette_rgb(palette_warning);
//        }else{
//            m_front_wave_color = get_palette_rgb(palette_success);
//        }
        UIFluid::render_wave();
    }

    void UIFluidAssist::stable_cb(bool stable) {
        UIFluid::stable_cb(stable);
        /* todo overflow */
        if (stable) {
            lv_obj_add_flag(m_bar_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(m_bottom_label, LV_OBJ_FLAG_HIDDEN);
            if (m_current_y > m_assist_bottom) {
                lv_label_set_text(m_bottom_label, "Not Yet");
                lv_obj_set_style_text_color(m_bottom_label, get_palette_rgb(palette_notice), 0);
            } else if (m_current_y < m_assist_top) {
                lv_label_set_text(m_bottom_label, "Too Much");
                lv_obj_set_style_text_color(m_bottom_label, get_palette_rgb(palette_warning), 0);
                lv_draw_arc_dsc_t desc = {.color=get_palette_rgb(palette_warning), .width=1, .opa=LV_OPA_COVER};
            } else {
                lv_label_set_text(m_bottom_label, "Good");
                lv_obj_set_style_text_color(m_bottom_label, lv_color_white(), 0);
            }
        } else {
            lv_obj_clear_flag(m_bar_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_pos(m_bar_label, (LV_HOR_RES - m_tank_size) / 2 - 28,
                           m_current_y + (LV_VER_RES - m_tank_size) / 2 - 8);
            lv_obj_add_flag(m_bottom_label, LV_OBJ_FLAG_HIDDEN);
        }
    }
}
