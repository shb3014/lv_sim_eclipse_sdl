//
// Created by Gordon on 2022/11/28.
//

#include "UIOffline.h"
#include "Anim/lang/Lang.h"

namespace UI {
    UIOffline::UIOffline()
            : Base(),
              m_canvas(lv_canvas_create(m_scr)),
              m_title(lv_label_create(m_scr)),
              m_desc(lv_label_create(m_scr))
    {

        m_input_used = true;
        lv_obj_set_width(m_desc, 280);

    }

    void UIOffline::start_routine() {
        Base::start_routine();
        anim_canvas_reset_asset();
        anim_canvas_bind_asset(m_canvas, "offline");
        anim_canvas_update(m_canvas);

        lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 0);

        lv_obj_align(m_title, LV_ALIGN_TOP_MID, 0, 10);
        lv_obj_align_to(m_desc, m_title, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    }

    void UIOffline::input_cb(input_t input) {
        Base::input_cb(input);
        if (input == UI_INPUT_LEFT) {
            //IvyNet::instance().net_offline_later();
        } else if (input == UI_INPUT_RIGHT) {
            //IvyNet::instance().net_offline_ignore();
        }
        //LvglDriver::instance().route_to_default();
    }
}
