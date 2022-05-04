//
// Created by sungaoran on 2022/4/30.
//

#include "UITest.h"
#include "tools.h"

UI::UITest::UITest() {
    m_step_label = lv_label_create(m_scr);
    m_value_label = lv_label_create(m_scr);
    m_desc_label = lv_label_create(m_scr);
    m_progress_bar = lv_bar_create(m_scr);

    label_set_style(m_step_label, &ba_30);
    label_set_style(m_value_label, &ba_40);
    label_set_style(m_desc_label, &ba_16);
    lv_label_set_recolor(m_desc_label, true);
    bar_set_default_style(m_progress_bar);
    lv_obj_set_size(m_progress_bar, 200, 20);

    lv_obj_align(m_step_label, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 70);
    lv_obj_align(m_desc_label, LV_ALIGN_CENTER, 0, 60);
    lv_obj_align(m_progress_bar, LV_ALIGN_CENTER, 0, 20);
}

void UI::UITest::update_step(const char *step) {
    lv_label_set_text(m_step_label, step);
}

void UI::UITest::update_desc(const char *desc) {
    lv_label_set_text(m_desc_label, desc);
}

void UI::UITest::update_value(const char *value) {
    lv_label_set_text(m_value_label, value);
}

void UI::UITest::update_progress(int progress, int anim_t) {
    if (anim_t) {
        lv_obj_set_style_anim_time(m_progress_bar, anim_t, 0);
        lv_bar_set_value(m_progress_bar, progress, LV_ANIM_ON);
        auto *bar = (lv_bar_t *) m_progress_bar;
        bar->cur_value_anim.anim_start = 0;
    } else {
        lv_bar_set_value(m_progress_bar, progress, LV_ANIM_OFF);
    }
}

void UI::UITest::reset_progress() {
    auto *bar = (lv_bar_t *) m_progress_bar;
    bar->cur_value = 0;
}

void UI::UITest::routine() {
    static int i = 0;
    if (i++ > 10) {
        printf("ok %d\n", lv_bar_get_mode(m_progress_bar));
//        reset_progress();
        update_progress(100,1);
        i = 0;
    }
}
