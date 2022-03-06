//
// Created by sungaoran on 2022/2/27.
//

#ifndef LVGL_UIACTIONBOX_H
#define LVGL_UIACTIONBOX_H

#include "UIBase.h"
#include "functional"

typedef std::function<void()> action_cb_t;

class UIActionBox : public UIBase {
public:
    void show() override;

    void update(const char *title, const char* desc, const char *left, const char *right, action_cb_t left_cb = nullptr,
                action_cb_t right_cb = nullptr, int counting_max=0);

    void routine();

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

    int m_counting_max = 0;
    int m_counting_t =0;
};


#endif //LVGL_UIACTIONBOX_H
