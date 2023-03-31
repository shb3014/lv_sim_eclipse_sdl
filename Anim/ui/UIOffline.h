//
// Created by Gordon on 2022/11/28.
//

#ifndef PLANTSIO_IVY_UIOFFLINE_H
#define PLANTSIO_IVY_UIOFFLINE_H

#include "Base.h"
#include "Components.h"

namespace UI {
    class UIOffline : public Base  {
    public:
        UIOffline();

        void start_routine() override;

        void input_cb(input_t input) override;

    private:
        lv_obj_t *m_title;
        lv_obj_t *m_desc;
        lv_obj_t *m_canvas;
//        SelectButton m_later_btn;
//        SelectButton m_ignore_btn;

    };
}


#endif //PLANTSIO_IVY_UIOFFLINE_H
