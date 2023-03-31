//
// Created by sungaoran on 2022/5/4.
//

#include "UIText.h"
#include "tools.h"

namespace UI {
    UIText::UIText()
            : m_text_main(m_scr),
              m_text_sub(m_scr) {

        m_text_main.set_text_font({.zh = Lang::mi_light_font_30,
                                   .en = Lang::ba_font_30,
                                   .jp = Lang::jp_font_30});
        m_text_sub.set_text_font({.zh = Lang::mi_light_font_16,
                                  .en = Lang::ba_font_16,
                                  .jp = Lang::jp_font_16});

        m_is_temp = true;
    }

    void UIText::update(const char *main, const char *sub, bool anim_on) {
        update_main(main, anim_on);
        update_sub(sub, anim_on);
        realign();
    }

    void UIText::update_main(const char *main, bool anim_on) {
        m_text_main.update(main, anim_on);
        realign();
    }

    void UIText::update_sub(const char *sub, bool anim_on) {
        m_text_sub.update(sub, anim_on);
        realign();
    }

    void UIText::realign() const {
        lv_obj_align(m_text_main.label, LV_ALIGN_CENTER, 0, -20);
        lv_obj_align_to(m_text_sub.label, m_text_main.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    }
}