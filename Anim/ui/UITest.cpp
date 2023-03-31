//
// Created by sungaoran on 2022/4/30.
//

#include "UITest.h"
#include "tools.h"

#include "Anim/lang/Lang.h"

UI::UITest::UITest() : Base() {
    m_input_used = true;
    m_step_label = lv_label_create(m_scr);
    m_value_label = lv_label_create(m_scr);
    m_desc_label = lv_label_create(m_scr);
    m_progress_bar = lv_bar_create(m_scr);

    Lang::Language::instance().lang_set_style_text_font(m_step_label, {.zh = Lang::mi_light_font_30,
                                                                       .en = Lang::ba_font_30,
                                                                       .jp = Lang::jp_font_30});
    Lang::Language::instance().lang_set_style_text_font(m_value_label, {.zh = Lang::mi_light_font_36,
                                                                        .en = Lang::ba_font_40,
                                                                        .jp = Lang::jp_font_36});
    Lang::Language::instance().lang_set_style_text_font(m_desc_label, {.zh = Lang::mi_light_font_16,
                                                                       .en = Lang::ba_font_16,
                                                                       .jp = Lang::jp_font_16});

    lv_label_set_recolor(m_desc_label, true);
    bar_set_default_style(m_progress_bar);
    lv_obj_set_size(m_progress_bar, 200, 20);

    lv_obj_align(m_step_label, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 70);
    lv_obj_align(m_desc_label, LV_ALIGN_CENTER, 0, 60);
    lv_obj_align(m_progress_bar, LV_ALIGN_CENTER, 0, 20);
    lv_label_set_text(m_value_label,"");
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

void UI::UITest::update_color(lv_color_t back_color, lv_color_t text_color) {
    lv_obj_set_style_bg_color(m_scr, back_color, 0);
    lv_obj_set_style_text_color(m_step_label, text_color, 0);
    lv_obj_set_style_text_color(m_value_label, text_color, 0);
    lv_obj_set_style_text_color(m_desc_label, text_color, 0);
}

void UI::UITest::input_cb(UI::input_t input) {
    Base::input_cb(input);
    if (input == UI_INPUT_LEFT) {
        left_touched = true;
    } else if (input == UI_INPUT_RIGHT) {
        right_touched = true;
    }
}

void UI::UITest::update(int progress, const char *step, const char *desc, lv_color_t color) {
    lv_bar_set_value(m_progress_bar, progress, LV_ANIM_OFF);
    lv_label_set_text(m_step_label, step);
    lv_label_set_text(m_desc_label, desc);
    lv_obj_set_style_bg_color(m_scr, color, 0);
}
