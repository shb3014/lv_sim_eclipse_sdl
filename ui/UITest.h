//
// Created by sungaoran on 2022/4/30.
//

#ifndef LVGL_UITEST_H
#define LVGL_UITEST_H

#include "Base.h"

namespace UI {
    class UITest : public Base {
    public:
        UITest();

        index_t get_index() override {
            return UI_TEST;
        }

        void update_step(const char *step);

        void update_desc(const char *desc);

        void update_value(const char *value);

        void update_progress(int progress, int anim_t = 0);

        void reset_progress();

        void routine() override;

    private:
        lv_obj_t *m_step_label;
        lv_obj_t *m_value_label;
        lv_obj_t *m_desc_label;
        lv_obj_t *m_progress_bar;

    };
}

#endif //LVGL_UITEST_H
