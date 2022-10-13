//
// Created by Huwensong on 2022/10/11.
//
#include "UIProvTip.h"
#include "tools.h"

#define TIP_CARD_WIDTH     200
#define TIP_CARD_HEIGHT    100

#define CARD_NUM           3

#define ANIM_TIME_START   0
#define ANIM_TIME_INTERVAL    6000   //ms


namespace UI
{
    static void anim_show_cb(void *var, int32_t value)
    {
        lv_obj_set_style_opa((lv_obj_t *) var, value, 0);
    }

    static void anim_fade_cb(void *var, int32_t value)
    {
        lv_obj_set_style_opa((lv_obj_t *) var, value, 0);
    }

    TipCard::TipCard(lv_obj_t *parent)
    {
        m_tip_card = lv_obj_create(parent);
        lv_obj_set_size(m_tip_card, TIP_CARD_WIDTH, TIP_CARD_HEIGHT);
        lv_obj_set_style_bg_opa(m_tip_card, LV_OPA_TRANSP, 0);
        lv_obj_set_style_opa(m_tip_card, LV_OPA_TRANSP, 0);
        lv_obj_set_style_radius(m_tip_card, 20, 0);
        lv_obj_clear_flag(m_tip_card, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_align(m_tip_card, LV_ALIGN_TOP_MID, 0, 80);

        m_tip_lable = lv_label_create(m_tip_card);
        label_set_style(m_tip_lable, &ba_16);
        lv_obj_align(m_tip_lable, LV_ALIGN_TOP_LEFT, 0, 0);
        lv_label_set_recolor(m_tip_lable, true);
        lv_label_set_text(m_tip_lable, "#ff0000 Tip:#");

        m_desc_lable = lv_label_create(m_tip_card);
        label_set_style(m_desc_lable, &ba_16);
        lv_obj_align(m_desc_lable, LV_ALIGN_TOP_LEFT, 10, 20);
        lv_label_set_text(m_desc_lable, "");
    }

    void TipCard::card_anim_create()
    {
        m_anim_show = anim_create(m_tip_card, anim_show_cb, LV_OPA_TRANSP, LV_OPA_COVER,
                                  3000, 0, 0, 0, nullptr,
                                  nullptr, 0, lv_anim_path_ease_in_out);
        lv_anim_set_early_apply(&m_anim_show, false);

        m_anim_fade = anim_create(m_tip_card, anim_fade_cb, LV_OPA_COVER, LV_OPA_TRANSP,
                                  3000, 0, 0, 0, nullptr,
                                  nullptr, 0, lv_anim_path_ease_in_out);
        lv_anim_set_early_apply(&m_anim_fade, false);

        m_anim_move = anim_create(m_tip_card, anim_move_hor, 0, -TIP_CARD_WIDTH,
                                  5000, 0, 0, 0, nullptr,
                                  nullptr, 0, lv_anim_path_overshoot);
        lv_anim_set_early_apply(&m_anim_move, false);
    }

    void TipCard::card_anim_begin()
    {
        m_anim_timeline = lv_anim_timeline_create();

        lv_anim_timeline_add(m_anim_timeline, m_anim_start_time, &m_anim_show);
        lv_anim_timeline_add(m_anim_timeline, m_anim_start_time + 4000, &m_anim_fade);
        lv_anim_timeline_add(m_anim_timeline, m_anim_start_time + 4000, &m_anim_move);

        lv_anim_timeline_start(m_anim_timeline);
    }

    void TipCard::update_tip_desc(const char *desc)
    {

        lv_label_set_text(m_desc_lable, desc);
    }


    void TipCard::card_anim_stop()
    {
        lv_anim_timeline_stop(m_anim_timeline);
    }

    void TipCard::set_anim_start_time(uint32_t time)
    {
        m_anim_start_time = time;
    }

    EndTipCard::EndTipCard(lv_obj_t *parent) : TipCard(parent)
    {

    }

    void EndTipCard::card_anim_create()
    {
        m_anim_end_tip = anim_create(m_tip_card, anim_show_cb, LV_OPA_TRANSP, LV_OPA_COVER,
                                     3000, 0, 0, 0, nullptr,
                                     nullptr, 0, lv_anim_path_ease_in_out);
        lv_anim_set_early_apply(&m_anim_end_tip, false);
    }

    void EndTipCard::card_anim_begin()
    {
        m_anim_timeline = lv_anim_timeline_create();

        lv_anim_timeline_add(m_anim_timeline, m_anim_start_time, &m_anim_end_tip);

        lv_anim_timeline_start(m_anim_timeline);
    }

    UIProvTip::UIProvTip() :
            Base(),
            m_tip_card(
                    {
                            TipCard(m_scr),
                            TipCard(m_scr),
                            TipCard(m_scr),
                    }
            ),
            m_end_tip_card(m_scr)
    {
        m_title_lable = lv_label_create(m_scr);
        label_set_style(m_title_lable, &ba_40);
        lv_obj_align(m_title_lable, LV_ALIGN_TOP_MID, 0, 30);
        lv_label_set_recolor(m_title_lable, true);

    }

    index_t UIProvTip::get_index()
    {
        return UI_PROV_TIP;
    }

    void UIProvTip::clear()
    {

    }

    void UIProvTip::routine()
    {
        update_desc();
        Base::routine();
    }

    void UIProvTip::start_routine()
    {
        uint32_t start_time = 0;
        for (auto itr = m_tip_card.begin(); itr < m_tip_card.end(); itr++)
        {
            itr->set_anim_start_time(start_time);
            itr->card_anim_create();
            itr->card_anim_begin();
            start_time += ANIM_TIME_INTERVAL;
        }

        m_end_tip_card.set_anim_start_time(start_time);
        m_end_tip_card.card_anim_create();
        m_end_tip_card.card_anim_begin();
    }

    void UIProvTip::input_cb(input_t input)
    {

    }

    void UIProvTip::update_desc()
    {
        lv_label_set_text(m_title_lable, "#00ff00 this is a title#");
        m_tip_card[0].update_tip_desc("this is a tip one!");
        m_tip_card[1].update_tip_desc("this is a tip two!");
        m_tip_card[2].update_tip_desc("this is a tip three!");
        m_end_tip_card.update_tip_desc("this is a end card!");
    }
}


