//
// Created by Gordon on 2023/2/15.
//

#ifndef TUYA_PLANTS_IVY_UINOSERVICE_H
#define TUYA_PLANTS_IVY_UINOSERVICE_H

#include "UIText.h"

#include "Anim/lang/Lang.h"

namespace UI {
    class UINoService : public UIText {
    public:
        UINoService() : UIText() {
            update(LANG(Lang::ui_no_service), LANG(Lang::ui_no_service_desc));
        }
    };
}

#endif //TUYA_PLANTS_IVY_UINOSERVICE_H
