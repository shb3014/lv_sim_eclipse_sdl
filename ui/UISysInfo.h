//
// Created by Gordon on 2021/12/2.
//

#ifndef PLANTSIO_IVY_UISYSINFO_H
#define PLANTSIO_IVY_UISYSINFO_H

#include "Base.h"
#include "Components.h"

namespace UI {
#define SYS_UI_HEIGHT       200

    class UISysInfo : public Base {
    public:
        UISysInfo();

        index_t get_index() override {
            return UI_SYS_INFO;
        }

        void update_info();

    private:
        lv_obj_t *m_table;
    };
}

#endif //PLANTSIO_IVY_UISYSINFO_H
