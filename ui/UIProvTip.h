//
// Created by Huwensong on 2022/10/11.
//

#ifndef LVGL_UIPROVTIP_H
#define LVGL_UIPROVTIP_H
#include "Base.h"

namespace UI
{
    class TipCard
    {
    public:
        TipCard(lv_obj_t *parent);

    public:
        void update_tip_desc(const char * desc);

        void card_anim_begin();

        void card_anim_stop();

        void set_anim_start_time(uint32_t time);

        bool is_anim_over();

    private:
        void card_anim_create();

    private:
        lv_obj_t *m_tip_card;

        lv_obj_t *m_tip_lable;
        lv_obj_t *m_desc_lable;

        lv_anim_timeline_t *m_anim_timeline;

        lv_anim_t m_anim_fade;
        lv_anim_t m_anim_show;
        lv_anim_t m_anim_move;

        uint32_t m_anim_start_time;
    };


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


    private:
        void update_desc();

    private:
        lv_obj_t *m_title_lable;

        std::vector<TipCard> m_tip_card;
    };
}



#endif //LVGL_UIPROVTIP_H
