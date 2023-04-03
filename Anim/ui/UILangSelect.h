//
// Created by Huwensong on 2023/3/31.
//

#ifndef LVGL_UILANGSELECT_H
#define LVGL_UILANGSELECT_H

#include <string>
#include "Base.h"

namespace UI
{
    class UILangSelect : public Base
    {
    public:
        UILangSelect();

        ~UILangSelect();

    public:

        void start_routine() override;

        void routine() override;

        void input_cb(input_t input) override;

        void front_input_cb(bool touch) override;

    private:
        void set_roller_style();

        void set_text_style();

        void update();

    private:
        lv_obj_t *m_roller;

        lv_obj_t *m_title;

        lv_obj_t *m_ok;

        lv_obj_t *m_front_touch;

        std::string m_lang_list;

        int m_lang_index = 1;
    };
}

#endif //LVGL_UILANGSELECT_H
