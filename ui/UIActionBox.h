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

        index_t get_index() override {
            return UI_ACTION;
        }

        void
        update(const char *title, const char *desc, const char *left, const char *right, action_cb_t left_cb = nullptr,
               action_cb_t right_cb = nullptr, int counting_max = 0);

        void routine() override;

        void set_action(action_t action) {
            m_action = action;
        }

        void input_cb(input_t input) override;

        void clear() override;

    private:
        lv_obj_t *m_title_label;
        lv_obj_t *m_desc_label;
        lv_obj_t *m_left_button;
        lv_obj_t *m_right_button;
        lv_obj_t *m_touch_left_label;
        lv_obj_t *m_touch_right_label;
        lv_obj_t *m_counting_arc;
        lv_obj_t *m_counting_label;
        action_cb_t m_left_cb;
        action_cb_t m_right_cb;

        uint32_t m_counting_timeout_t = 0;
        uint32_t m_counting_max = 60;
        action_t m_action = ACTION_WAITING;
    };
}

#endif //LVGL_UIACTIONBOX_H
