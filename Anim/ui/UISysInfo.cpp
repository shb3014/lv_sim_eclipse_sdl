//
// Created by Gordon on 2021/12/2.
//

#include "UISysInfo.h"

#include "Anim/lang/Lang.h"
#include "Anim/lang/Lang.h"

namespace UI
{
    static void draw_cb(lv_event_t *e)
    {
        lv_obj_t *obj = lv_event_get_target(e);
        auto *dsc = (lv_obj_draw_part_dsc_t *) lv_event_get_param(e);
        if (dsc->part == LV_PART_ITEMS)
        {
            uint32_t row = dsc->id / lv_table_get_col_cnt(obj);
            uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);
            if (col == 0)
            {
                dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;
            }
            //dsc->label_dsc->font = &ba_16;
            dsc->label_dsc->color = lv_color_white();
            dsc->rect_dsc->border_color = lv_color_make(154, 215, 253);
            dsc->rect_dsc->border_side = LV_BORDER_SIDE_FULL;
        }
    }

    UISysInfo::UISysInfo()
            : Base(),
              m_table(lv_table_create(m_scr))
    {
//        m_input_used = true;
//        set_routable_indicator_visible(true, right);

        Lang::Language::instance().lang_set_style_text_font(m_table,
                                                            {.zh = Lang::mi_light_font_14,
                                                                       .en = Lang::ba_font_16,
                                                                       .jp = Lang::jp_font_14});
        update_info();
        lv_obj_set_size(m_table, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_center(m_table);
        lv_obj_clear_flag(m_table, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_bg_opa(m_table, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_opa(m_table, LV_OPA_TRANSP, 0);
        lv_obj_set_style_pad_ver(m_table, 8, LV_PART_ITEMS);
        lv_obj_set_style_bg_opa(m_table, LV_OPA_TRANSP, LV_PART_ITEMS);
        lv_obj_add_event_cb(m_table, draw_cb, LV_EVENT_DRAW_PART_BEGIN, nullptr);
    }

    void UISysInfo::update_info()
    {
        lv_table_set_cell_value(m_table, 0, 0, Lang::Text::instance().get_text(
                Lang::ui_sysinfo_wifi_name).c_str());
        lv_table_set_cell_value(m_table, 1, 0, Lang::Text::instance().get_text(
                Lang::ui_sysinfo_public_ip).c_str());
        lv_table_set_cell_value(m_table, 2, 0,
                                Lang::Text::instance().get_text(Lang::ui_sysinfo_local_ip).c_str());
        lv_table_set_cell_value(m_table, 4, 0,
                                Lang::Text::instance().get_text(Lang::ui_sysinfo_ota_ver).c_str());
        lv_table_set_cell_value(m_table, 5, 0,
                                Lang::Text::instance().get_text(Lang::ui_sysinfo_evolve).c_str());
        lv_table_set_cell_value(m_table, 3, 0,
                                Lang::Text::instance().get_text(Lang::ui_sysinfo_location).c_str());

        lv_table_set_cell_value(m_table, 0, 1, "Ivytest");
        lv_table_set_cell_value(m_table, 1, 1, "172.171.170,160");
        lv_table_set_cell_value(m_table, 2, 1, "192.168.20.45");
        lv_table_set_cell_value(m_table, 3, 1, "TianJin");
        lv_table_set_cell_value(m_table, 4, 1, "1.1.6");

        lv_obj_center(m_table);
        time_t t = 1676969310;
        tm *info = localtime(&t);
        std::string t_str = std::to_string(info->tm_year + 1900) + "-" + std::to_string(info->tm_mon) + "-" +
                            std::to_string(info->tm_mday);
        lv_table_set_cell_value(m_table, 5, 1, t_str.c_str());

    }

    void UISysInfo::input_cb(input_t input)
    {
//        Base::input_cb(input);
//        if (input == UI_INPUT_RIGHT) {
//            static lv_coord_t current_p = 0;
//            if (current_p > lv_obj_get_height(m_table)) {
//                current_p = 0;
//            } else {
//                current_p += SYS_UI_HEIGHT;
//            }
//            lv_obj_scroll_to_y(m_table, current_p, LV_ANIM_ON);
//        }
    }
}