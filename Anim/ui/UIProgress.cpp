//
// Created by sungaoran on 2021/11/16.
//

#include "UIProgress.h"
#include "tools.h"

#include "Anim/lang/Lang.h"

namespace UI
{
    UIProgress::UIProgress() : Base()
    {

        m_bar = lv_bar_create(m_scr);
        bar_set_default_style(m_bar);

        lv_obj_set_size(m_bar, 200, 20);
        lv_obj_center(m_bar);

        m_title_label = lv_label_create(m_scr);
        lv_obj_set_width(m_title_label, 200);
        Lang::Language::instance().lang_set_style_text_font(m_title_label,
                                                            {.zh = Lang::mi_light_font_30,
                                                             .en = Lang::ba_font_30,
                                                             .jp = Lang::jp_font_24});
        lv_obj_align_to(m_title_label, m_bar, LV_ALIGN_OUT_TOP_MID, 0, -30);

        m_status_label = lv_label_create(m_scr);
        lv_obj_set_width(m_status_label, 240);
        Lang::Language::instance().lang_set_style_text_font(m_status_label,
                                                            {.zh = Lang::mi_light_font_16,
                                                                       .en = Lang::ba_font_16,
                                                                       .jp = Lang::jp_font_16});
        lv_obj_align_to(m_status_label, m_bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        lv_label_set_recolor(m_status_label, true);

        m_desc_label = lv_label_create(m_scr);
        lv_obj_set_width(m_desc_label, 280);
        Lang::Language::instance().lang_set_style_text_font(m_desc_label,
                                                            {.zh = Lang::mi_light_font_16,
                                                                    .en = Lang::ba_font_16,
                                                                    .jp = Lang::jp_font_16});
        lv_label_set_recolor(m_desc_label, true);
        lv_obj_align_to(m_desc_label, m_status_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 12);
        lv_label_set_text(m_desc_label, "");

    }

    void UIProgress::update_title(const char *value)
    {
        lv_label_set_text(m_title_label, value);
    }

    void UIProgress::update_status(const char *value)
    {
        lv_label_set_text(m_status_label, value);
    }

    void UIProgress::update_progress(uint8_t progress)
    {
        lv_bar_set_value(m_bar, progress, LV_ANIM_OFF);
    }

    void UIProgress::update_desc(const char *desc)
    {
        lv_label_set_text(m_desc_label, desc);
    }

    void UIProgress::update(const char *status, uint8_t progress)
    {
        if (std::string(status) != lv_label_get_text(m_status_label))
        {
            /* update status */
            update_status(status);
        }
        update_progress(progress);
    }

    void UIProgress::update(const char *title, const char *status, uint8_t progress)
    {
        if (std::string(title) != lv_label_get_text(m_title_label))
        {
            /* update title */
            update_title(title);

        }
        update(status, progress);
    }
}