//
// Created by Huwensong on 2022/10/11.
//

#ifndef LVGL_UIPROVTIP_H
#define LVGL_UIPROVTIP_H

#include "Base.h"
#include "Components.h"

namespace UI
{
    typedef enum
    {
        prov_init,
        prov_ap_sta_connected,
        prov_get_info,
        prov_sta_connected,
        prov_finished,
    }prov_status_t;

    class UIProvTip : public Base
    {
    public:
        UIProvTip();

    public:
        index_t get_index() override;

        void clear() override;

        void routine() override;

        void start_routine() override;

        void input_cb(input_t input) override;

        void ui_prov_set_status(prov_status_t status);


    private:
        void update_title(const char *content);

        void update_tip(const char *content);

        void next();

        static void timer_cb(lv_timer_t *timer);

    private:
        prov_status_t m_prov_status;

        BasicText m_tip_title_text;
        BasicText m_tip_content_text;

        lv_timer_t *m_timer;
    };
}


#endif //LVGL_UIPROVTIP_H
