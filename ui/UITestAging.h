//
// Created by Gordon on 2022/11/9.
//

#ifndef PLANTSIO_IVY_UITESTAGING_H
#define PLANTSIO_IVY_UITESTAGING_H

#include "Base.h"

namespace UI {


    class UITestAging : public Base {
    public:
        UITestAging();

        index_t get_index() override {
            return UI_TEST_AGING;
        }

        void update(uint32_t time, int progress, int timeout, const char *content, lv_color_t bck_color = lv_color_black(),
                    lv_color_t text_color = lv_color_white());

        void routine() override;

        void start_routine() override;

    private:
        lv_obj_t *m_time_label;
        lv_obj_t *m_test_anim;
        lv_obj_t *m_charging_bar;
        lv_obj_t *m_charging_label;
        lv_obj_t *m_timeout_label;

    };

}


#endif //PLANTSIO_IVY_UITESTAGING_H
