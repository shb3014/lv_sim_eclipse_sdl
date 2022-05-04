//
// Created by Gordon on 2022/2/24.
//

#ifndef LVGL_UIDOUBLEPROGRESS_H
#define LVGL_UIDOUBLEPROGRESS_H

#include "Base.h"
namespace UI {
    class UIDoubleProgress : public Base {
    public:
        UIDoubleProgress();

        index_t get_index() override {
            return UI_DOUBLE_PROGRESS;
        }

        void
        update(const char *title, const char *status_1, uint8_t progress_1, const char *status_2, uint8_t progress_2);

        void update_progress_1(const char *status_1, uint8_t progress_1);

        void update_progress_2(const char *status_2, uint8_t progress_2);

    private:
        lv_obj_t *m_bar_1;
        lv_obj_t *m_bar_2;
        lv_obj_t *m_title_label;
        lv_obj_t *m_status_label_1;
        lv_obj_t *m_status_label_2;

    };
}
#endif //LVGL_UIDOUBLEPROGRESS_H
