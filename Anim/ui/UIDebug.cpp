//
// Created by Gordon on 2022/6/13.
//

#include "UIDebug.h"
#include "tools.h"

namespace UI {
    UIDebug::UIDebug()
            : Base(),
              m_value_label(m_scr),
              m_value_label_2(m_scr),
              m_value_label_3(m_scr),
              m_ip_label(m_scr) {

        m_value_label.set_text_font({.zh = Lang::mi_light_font_30,
                                     .en = Lang::ba_font_30,
                                     .jp = Lang::jp_font_30});
        m_value_label_2.set_text_font({.zh = Lang::mi_light_font_30,
                                       .en = Lang::ba_font_30,
                                       .jp = Lang::jp_font_30});
        m_value_label_3.set_text_font({.zh = Lang::mi_light_font_16,
                                       .en = Lang::ba_font_16,
                                       .jp = Lang::jp_font_16});
        m_ip_label.set_text_font({.zh = Lang::mi_light_font_16,
                                  .en = Lang::ba_font_16,
                                  .jp = Lang::jp_font_16});

        lv_obj_align(m_ip_label.label, LV_ALIGN_CENTER, 0, -40);
        lv_obj_align(m_value_label.label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_align(m_value_label_2.label, LV_ALIGN_CENTER, 0, 60);
        lv_obj_align_to(m_value_label_3.label, m_value_label_2.label, LV_ALIGN_BOTTOM_MID, 0, 10);
        m_ip_label.update("192.168.20.15");
    }

    void UIDebug::routine() {
        Base::routine();
        //int value = sense.get_current_soil_raw();
        m_value_label.update(("raw: " + std::to_string(50)).c_str());
//        int mapped_value = Sense::instance().get_current_soil_moisture();
//        if (sense.avg_soil_moisture_stable()) {
//            int mapped_value = sense.get_current_soil_moisture();
//            m_value_label_2.update(("mapped: " + std::to_string(mapped_value)).c_str());
//        } else {
//            m_value_label_2.update("stabilizing");
//        }
//        std::string v_str = "cnt: " + std::to_string(Prop::get<int>(Prop::water_present_cnt)) + " | " +
//                            std::to_string(Prop::get<uint32_t>(Prop::water_last_present_t));
        std::string v_str = "cnt: " + std::to_string(60);
        m_value_label_3.update(v_str.c_str());
    }
}