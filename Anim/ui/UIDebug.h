//
// Created by Gordon on 2022/6/13.
//

#ifndef PLANTSIO_IVY_UIDEBUG_H
#define PLANTSIO_IVY_UIDEBUG_H

#include "Base.h"
#include "Components.h"

namespace UI {
    class UIDebug : public Base {
    public:
        UIDebug();

        void routine() override;

    private:
        BasicText m_ip_label;
        BasicText m_value_label;
        BasicText m_value_label_2;
        BasicText m_value_label_3;

    };
}

#endif //PLANTSIO_IVY_UIDEBUG_H
