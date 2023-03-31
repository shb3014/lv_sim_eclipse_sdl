//
// Created by sungaoran on 2021/11/16.
//

#ifndef PLANTSIO_IVY_UIPROGRESS_H
#define PLANTSIO_IVY_UIPROGRESS_H

#include "Base.h"
namespace UI {
    class UIProgress : public Base {
    public:
        UIProgress();

        void update(const char *title, const char *status, uint8_t progress);

        void update(const char *status, uint8_t progress);

        void update_title(const char *value);

        void update_status(const char *value);

        void update_progress(uint8_t progress);

        void update_desc(const char *desc);

    private:
        lv_obj_t *m_bar;
        lv_obj_t *m_title_label;
        lv_obj_t *m_status_label;
        lv_obj_t *m_desc_label;
    };
}

#endif //PLANTSIO_IVY_UIPROGRESS_H
