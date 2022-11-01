//
// Created by Huwensong on 2022/10/11.
//
#include "UIProvTip.h"
#include "tools.h"

#define PROV_TIP_DELAY     6500


namespace UI
{
    UIProvTip::UIProvTip() : Base(),
    m_tip_title_text(m_scr,&ba_40),
    m_tip_content_text(m_scr,&ba_16)
    {
        m_prov_status = prov_init;
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
        Base::routine();
        update_title(get_colored_str("ProvisionTip",palette_notice).c_str());
    }

    void UIProvTip::start_routine()
    {
//        uint32_t start_time = 0;
//        for (auto itr = m_tip_card.begin(); itr < m_tip_card.end(); itr++)
//        {
//            itr->set_anim_start_time(start_time);
//            itr->card_anim_create();
//            itr->card_anim_begin();
//            start_time += ANIM_TIME_INTERVAL;
//        }
//
//        m_end_tip_card.set_anim_start_time(start_time);
//        m_end_tip_card.card_anim_create();
//        m_end_tip_card.card_anim_begin();

        Base::start_routine();
        m_timer = lv_timer_create(timer_cb, PROV_TIP_DELAY, this);
        lv_timer_ready(m_timer);

    }

    void UIProvTip::input_cb(input_t input)
    {

    }

    void UIProvTip::ui_prov_set_status(prov_status_t status)
    {
        m_prov_status = status;
    }

    void UIProvTip::update_title(const char *content)
    {
        m_tip_title_text.update(content, false);
        lv_obj_align(m_tip_title_text.label, LV_ALIGN_TOP_MID, 0, 10);
    }

    void UIProvTip::update_tip(const char *content)
    {
        m_tip_content_text.update(content);
        realign();
    }

    void UIProvTip::realign()
    {
        lv_obj_align(m_tip_content_text.label, LV_ALIGN_CENTER, 0, 0);
    }

    void UIProvTip::next()
    {
        static int i = 0;
        switch (m_prov_status)
        {
            case prov_init:
                break;
            case prov_ap_sta_connected:
                update_tip("The mobile phone connected!");
                break;
            case prov_get_info:
                update_tip("Got information of router!");
                break;
            case prov_sta_connected:
                update_tip("Success to connect router!");
                break;
            case prov_finished:
                update_tip("Complete! Waiting for reboot!");
                break;
            default:
                break;
        }
        i++;
        m_prov_status  = (prov_status_t) i;
    }

    void UIProvTip::timer_cb(lv_timer_t *timer)
    {
        auto ui = static_cast<UIProvTip *>(timer->user_data);
        ui->next();
    }
}


