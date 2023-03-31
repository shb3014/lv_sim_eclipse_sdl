//
// Created by sungaoran on 2022/2/27.
//

#ifndef LVGL_UIACTIONBOX_H
#define LVGL_UIACTIONBOX_H

#include "Base.h"
#include "functional"

namespace UI {
    typedef std::function<void()> action_cb_t;

    typedef enum {
        ACTION_WAITING = 0,
        ACTION_APPLY = 1,
        ACTION_CANCEL = 2,
        ACTION_OVER = 2,
    } action_t;

    class UIActionBox : public Base {
    public:
        UIActionBox();

        void start_routine() override;

        void
        update(const char *title, const char *desc, const char *apply_desc, const char *cancel_desc, action_cb_t apply_cb = nullptr,
               action_cb_t cancel_cb = nullptr, action_cb_t final_cb = nullptr, int counting_max = 0);

        void routine() override;

        void set_action(action_t action) {
            m_action = action;
        }

        void clear() override;

        void input_cb(input_t input) override;

    private:
        lv_obj_t *m_title_label;
        lv_obj_t *m_desc_label;
        lv_obj_t *m_left_button;
        lv_obj_t *m_right_button;
        lv_obj_t *m_touch_left_label;
        lv_obj_t *m_touch_right_label;
        lv_obj_t *m_counting_arc;
        lv_obj_t *m_counting_label;
        action_cb_t m_cancel_cb;
        action_cb_t m_apply_cb;
        action_cb_t m_final_cb;

        uint32_t m_counting_timeout_t = 0;
        uint32_t m_counting_max = 60;
        action_t m_action = ACTION_WAITING;

        bool m_final_executed = false;
    };
}

#endif //LVGL_UIACTIONBOX_H
