//
// Created by Gordon on 2022/11/4.
//

#ifndef LVGL_UITESTERROR_H
#define LVGL_UITESTERROR_H

#include "Base.h"

namespace UI {
    class UITestError : public Base {
    public:
        UITestError();

        void set_errors(std::vector<int> &list);

    private:
        lv_obj_t *m_title_label;
        lv_obj_t *m_error_table;
    };

}
#endif //LVGL_UITESTERROR_H
