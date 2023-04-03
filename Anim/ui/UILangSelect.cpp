//
// Created by Huwensong on 2023/3/31.
//

#include "UILangSelect.h"
#include "lvgl/lvgl.h"
#include "Anim/lang/Lang.h"


namespace UI
{
    UILangSelect::UILangSelect() : Base()
    {
        m_lang_list = "Chinese\nEnglish\nJapanese\n";

        set_routable_indicator_visible(true);

        set_roller_style();
        set_text_style();
    }

    UILangSelect::~UILangSelect()
    {

    }

    void UILangSelect::start_routine()
    {
        update();
    }

    void UILangSelect::routine()
    {
        lv_roller_set_selected(m_roller, m_lang_index, LV_ANIM_OFF);
    }

    void UILangSelect::input_cb(input_t input)
    {
        int index_min = 0;
        int index_max = Lang::lang_max - 1;
        if (input == UI_INPUT_LEFT)
        {
            printf("UI_INPUT_LEFT\n");
            if (m_lang_index > index_min)
                m_lang_index --;
            else
                m_lang_index = index_min;
        }
        else if (input == UI_INPUT_RIGHT)
        {
            printf("UI_INPUT_RIGHT\n");
            if (m_lang_index < index_max)
                m_lang_index ++;
            else
                m_lang_index = index_max;
        }
        else
        {
            ; //
        }

    }

    void UILangSelect::front_input_cb(bool touch)
    {
        if (touch)
        {
            Lang::set_language((Lang::lang_t) m_lang_index);
            printf("set language successfully!! language = %d\n",m_lang_index);
        }
    }

    void UILangSelect::set_roller_style()
    {
        static lv_style_t style;
        lv_style_init(&style);
        lv_style_set_radius(&style,5);
        lv_style_set_bg_color(&style, lv_color_black());
        lv_style_set_text_color(&style, lv_color_white());
        lv_style_set_border_width(&style, 0);
        lv_style_set_pad_all(&style, 0);

        m_roller = lv_roller_create(m_scr);
        lv_obj_add_style(m_roller, &style, 0);
        lv_obj_set_style_bg_opa(m_roller, LV_OPA_30, LV_PART_SELECTED);
        lv_obj_set_style_text_font(m_roller, &ba_30, LV_PART_SELECTED);
        lv_roller_set_options(m_roller,m_lang_list.c_str(),LV_ROLLER_MODE_NORMAL);

        lv_obj_center(m_roller);
        lv_roller_set_visible_row_count(m_roller, 3);
        lv_obj_set_width(m_roller, 200);


    }

    void UILangSelect::set_text_style()
    {

        m_title = lv_label_create(m_scr);
        lv_obj_align(m_title, LV_ALIGN_TOP_MID, 0, 10);
        lv_obj_set_style_text_color(m_title, lv_color_white(),0);
        lv_obj_set_style_text_font(m_title, &ba_40, 0);
        lv_label_set_text(m_title, "Language");

        m_ok = lv_label_create(m_scr);
        lv_obj_align(m_ok, LV_ALIGN_BOTTOM_MID, 0, -25);
        lv_obj_set_style_text_color(m_ok, lv_color_make(245, 203, 38),0);
        lv_obj_set_style_text_font(m_ok, &ba_16, 0);
        lv_label_set_text(m_ok, "OK");

        m_front_touch = lv_label_create(m_scr);
        lv_obj_align(m_front_touch, LV_ALIGN_BOTTOM_MID, 0, -10);
        lv_obj_set_style_text_color(m_front_touch, lv_color_white(),0);
        lv_obj_set_style_text_font(m_front_touch, &ba_16, 0);
        lv_label_set_text(m_front_touch, "front touch");

    }

    void UILangSelect::update()
    {
        auto a = anim_create(m_front_touch, anim_fade, LV_OPA_TRANSP,LV_OPA_COVER,
                             500, 0, 1200, 1800,
                             nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&a);
    }

}
