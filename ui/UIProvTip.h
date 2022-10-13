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
        virtual void card_anim_create();

        virtual void card_anim_begin();

        void update_tip_desc(const char *desc);

        void card_anim_stop();

        void set_anim_start_time(uint32_t time);

    protected:
        lv_obj_t *m_tip_card;

        uint32_t m_anim_start_time;

        lv_anim_timeline_t *m_anim_timeline;

    private:
        lv_obj_t *m_tip_lable;
        lv_obj_t *m_desc_lable;

        lv_anim_t m_anim_fade;
        lv_anim_t m_anim_show;
        lv_anim_t m_anim_move;
    };

    class EndTipCard : public TipCard
    {
    public:
        EndTipCard(lv_obj_t *parent);

    public:
        void card_anim_create() override;

        void card_anim_begin() override;

    private:
        lv_anim_t m_anim_end_tip;

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
        EndTipCard m_end_tip_card;
    };
}


#endif //LVGL_UIPROVTIP_H
