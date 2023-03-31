//
// Created by Gordon on 2022/5/6.
//

#include "TutorialUI.h"
#include "tools.h"

#include "memory"
#include "UILoading.h"
#include "Anim/lang/Lang.h"

namespace UI {

    //region TuBase
    TuBase::TuBase() {}

    void TuBase::start_routine() {
        Base::start_routine();
        m_timer = lv_timer_create(timer_cb, TU_INTRO_DELAY, this);
        lv_timer_ready(m_timer);
    }

    void TuBase::clear() {
        if (m_timer) {
            lv_timer_del(m_timer);
        }
        Base::clear();
    }

    void TuBase::timer_cb(lv_timer_t *timer) {
        auto ui = static_cast<TuIntro *>(timer->user_data);
        ui->next();
    }

    void TuBase::fade_indicator(routable_indicator_part part, bool on, uint32_t time, uint32_t delay) {
        if (on) {
            set_routable_indicator_visible(true, part);
        }
        auto a = anim_create(m_routable_indicators[part], anim_fade, on ? LV_OPA_TRANSP : LV_OPA_COVER,
                             on ? LV_OPA_COVER : LV_OPA_TRANSP, time, delay);
        lv_anim_set_early_apply(&a, true);
        lv_anim_start(&a);
    }

    void TuBase::input_cb(input_t input) {
        Base::input_cb(input);
        if (input == UI_INPUT_LEFT) {
            m_left_touched = true;
        } else if (input == UI_INPUT_RIGHT) {
            m_right_touched = true;
        }
    }
    //endregion

    TuCanvasBase::TuCanvasBase()
            : TuBase(),
              m_top_text(m_scr, 250),
              m_bottom_text(m_scr, 250) {
        m_top_text.set_text_font({.zh = Lang::mi_light_font_16,
                                  .en = Lang::ba_font_16,
                                  .jp = Lang::jp_font_16});
        m_bottom_text.set_text_font({.zh = Lang::mi_light_font_16,
                                     .en = Lang::ba_font_16,
                                     .jp = Lang::jp_font_16});

        m_input_used = true;
        m_canvas = lv_canvas_create(m_scr);
        anim_canvas_reset_asset();

        lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 0);
        lv_obj_align(m_top_text.label, LV_ALIGN_TOP_MID, 0, 20);
        lv_obj_align(m_bottom_text.label, LV_ALIGN_BOTTOM_MID, 0, -10);
    }

    //region intro
    TuIntro::TuIntro()
            : TuBase(),
              m_top_text(m_scr),
              m_bottom_text(m_scr) {

        m_top_text.set_text_font({.zh = Lang::mi_light_font_30,
                                  .en = Lang::ba_font_30,
                                  .jp = Lang::jp_font_30});
        m_bottom_text.set_text_font({.zh = Lang::mi_light_font_16,
                                     .en = Lang::ba_font_16,
                                     .jp = Lang::jp_font_16});
    }

    void TuIntro::update(const char *main, const char *sub) {
        update_main(main);
        update_sub(sub);
        realign();
    }

    void TuIntro::update_main(const char *main) {
        m_top_text.update(main);
        realign();
    }

    void TuIntro::update_sub(const char *sub) {
        m_bottom_text.update(sub);
        realign();
    }

    void TuIntro::realign() const {
        lv_obj_align(m_top_text.label, LV_ALIGN_CENTER, 0, -20);
        lv_obj_align_to(m_bottom_text.label, m_top_text.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    }

    void TuIntro::next() {
        switch (m_current_step++) {
            case 0:
                update(Lang::Text::instance().get_text(Lang::ui_tu_intro_hi).c_str(), "");
                break;
            case 1:
                update_main(Lang::Text::instance().get_text(Lang::ui_tu_intro_ivy).c_str());
                break;
            case 2:
                update_main(Lang::Text::instance().get_text(Lang::ui_tu_intro_meet).c_str());
                break;
            case 3:
                update_main(Lang::Text::instance().get_text(Lang::ui_tu_intro_before_enter).c_str());
                break;
            case 4:
                update_main(Lang::Text::instance().get_text(Lang::ui_tu_intro_ready).c_str());
                break;
            case 5:
                update_sub(Lang::Text::instance().color_in_str(palette_notice,
                                                               Lang::Text::instance().get_text(
                                                                       Lang::ui_tu_intro_shutdown)).c_str());
                break;
            case 6:
                update("", "");
                lv_timer_set_period(m_timer, 2000);
                break;
            case 7:
#ifdef Ivy
                auto ui = UI::build_ui<TuTouchBar>(UI::TU_TOUCH_BAR);
                LvglDriver::instance().load(ui);
#endif
                break;
        }
    }
    //endregion

    TuTouchBar::TuTouchBar() : TuCanvasBase() {
        anim_canvas_bind_asset(m_canvas, "tu/tu_ivy");
        anim_canvas_update(m_canvas);


        m_top_text.update(Lang::Text::instance().get_text(Lang::ui_tu_touch_bar_interact).c_str());
        for (auto &circle: m_circles) {
            circle = lv_arc_create(m_scr);
            lv_obj_set_size(circle, 50, 50);
            lv_obj_set_style_arc_width(circle, 2, 0);
            lv_obj_set_style_arc_width(circle, 2, LV_PART_INDICATOR);
            lv_arc_set_rotation(circle, 0);
            lv_arc_set_value(circle, 0);
            lv_arc_set_bg_angles(circle, 0, 0);
            lv_obj_set_style_arc_color(circle, get_palette_rgb(palette_failure), 0);
            lv_obj_remove_style(circle, NULL, LV_PART_KNOB);
            lv_obj_clear_flag(circle, LV_OBJ_FLAG_CLICKABLE);
        }
        lv_obj_align(m_circles[0], LV_ALIGN_CENTER, -80, 10);
        lv_obj_align(m_circles[1], LV_ALIGN_CENTER, 80, 10);
    }

    void TuTouchBar::next() {
        switch (m_current_step) {
            case 0: {
                m_top_text.update(Lang::Text::instance().get_text(Lang::ui_tu_touch_bar_two).c_str());
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1000);
                lv_anim_start(&a);
                lv_timer_set_period(m_timer, 3000);
                break;
            }
            case 1: {
                for (auto &circle: m_circles) {
                    lv_obj_clear_flag(circle, LV_OBJ_FLAG_HIDDEN);
                    auto a = anim_create(circle, reinterpret_cast<lv_anim_exec_xcb_t>(lv_arc_set_bg_end_angle), 0, 360,
                                         2000);
                    lv_anim_start(&a);
                }
                lv_timer_set_period(m_timer, TU_INTRO_DELAY);
                break;
            }
            case 2: {
                m_top_text.update(Lang::Text::instance().color_in_str(palette_notice,
                                                                      Lang::Text::instance().get_text(
                                                                              Lang::ui_tu_touch_bar_yellow_dot)).c_str());
                for (auto &circle: m_circles) {
                    lv_obj_clear_flag(circle, LV_OBJ_FLAG_HIDDEN);
                    auto a = anim_create(circle, anim_fade, LV_OPA_COVER, LV_OPA_TRANSP, 2000);
                    lv_anim_start(&a);
                }
                lv_timer_set_period(m_timer, 4000);
                break;
            }
            case 3: {
                set_routable_indicator_visible(true);
                for (auto &indic: m_routable_indicators) {
                    auto a = anim_create(indic, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 0, 1000, 800, nullptr,
                                         nullptr, 2);
                    lv_anim_start(&a);
                }
                lv_timer_set_period(m_timer, 5000);
                break;
            }
            case 4: {
                m_left_touched = false;
                lv_timer_set_period(m_timer, 10);
                m_bottom_text.update(Lang::Text::instance().get_text(Lang::ui_tu_touch_bar_left).c_str());
                fade_indicator(left, true, 1000, 2000);
                break;
            }
            case 5: {
                if (!m_left_touched) {
                    return;
                }
                m_bottom_text.update(Lang::Text::instance().get_text(Lang::ui_tu_touch_bar_right).c_str(), false);
                fade_indicator(left, false, 600);
                fade_indicator(right, true, 600);
                m_right_touched = false;
                break;
            }
            case 6: {
                if (!m_right_touched) {
                    return;
                }
                m_bottom_text.update(Lang::Text::instance().get_text(Lang::ui_tu_touch_bar_great).c_str(), false);
                fade_indicator(left, true, 600);
                lv_timer_set_period(m_timer, 2000);
                break;
            }
            case 7: {
//                fade_indicator(left, false, 1000);
//                fade_indicator(right, true, 1000);
//                m_top_text.update("");
                //auto ui = UI::build_ui<TuApp>(UI::TU_APP);
                //LvglDriver::instance().load(ui);
                break;
            }
        }
        m_current_step++;
    }

    TuProvFail::TuProvFail()
            : TuBase(),
              m_text(m_scr) {

        m_text.set_text_font({.zh = Lang::mi_light_font_30,
                              .en = Lang::ba_font_30,
                              .jp = Lang::jp_font_30});

        lv_obj_set_align(m_text.label, LV_ALIGN_CENTER);
    }

    void TuProvFail::start_routine() {
        TuBase::start_routine();
    }

    void TuProvFail::next() {
        switch (m_current_step) {
            case 0:
                m_text.update(Lang::Text::instance().get_text(Lang::ui_tu_prov_fail).c_str());
                lv_timer_set_period(m_timer, 3000);
                break;
            case 1: {
                m_text.update(Lang::Text::instance().get_text(Lang::ui_tu_loading).c_str());
            }
        }
        m_current_step++;
    }

    TempText::TempText()
            : TuBase(),
              m_text(m_scr) {
        m_text.set_text_font({.zh = Lang::mi_light_font_16,
                              .en = Lang::ba_font_16,
                              .jp = Lang::jp_font_16});
        lv_obj_set_align(m_text.label, LV_ALIGN_CENTER);
    }

    void TempText::start_routine() {
        TuBase::start_routine();
    }

    void TempText::next() {
        switch (m_current_step) {
            case 0:
                m_text.update(m_target_text.c_str());
                lv_timer_set_period(m_timer, m_period);
                break;
            case 1: {
                m_text.update("");
            }
            case 2: {
                if (m_next_ui == UI_NULL) {
                    //LvglDriver::instance().route_to_default();
                } else {
                    //LvglDriver::instance().load(m_next_ui);
                }
            }
        }
        m_current_step++;
    }

    TuWater::TuWater() : TuCanvasBase() {
        lv_obj_align(m_top_text.label, LV_ALIGN_TOP_MID, 0, 15);
    }

    void TuWater::next() {
        switch (m_current_step) {
            case 0: {
                m_top_text.update(Lang::Text::instance().get_text(Lang::ui_tu_water_prepare_plant).c_str());
                lv_timer_set_period(m_timer, 4500);
                break;
            }
            case 1: {
                m_top_text.update(get_colored_str(Lang::Text::instance().get_text(Lang::ui_tu_water_remove_pot).c_str(),
                                                  palette_notice).c_str());
//                m_top_text.update("Please add 20mL of Water")
                anim_canvas_bind_asset(m_canvas, "tu/tu_water");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, -5, 10);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1500);
                lv_anim_start(&a);
                break;
            }
            case 2: {
                m_top_text.update(Lang::Text::instance().get_text(Lang::ui_tu_water_right_next).c_str());
                fade_indicator(right, true, 1000, 1500);
                lv_timer_set_period(m_timer, 1);
                m_right_touched = false;
                break;
            }
            case 3: {
                if (!m_right_touched) {
                    return;
                }
                //auto ui = UI::build_ui<TuWaterAssist>(TU_WATER_ASSIST);
                //LvglDriver::instance().load(ui, true, true, true);
                break;
            }
        }
        m_current_step++;
    }

    TuWaterAssist::TuWaterAssist() :
            TuCanvasBase(),
            m_middle_text(m_scr) {
        m_middle_text.set_text_font({.zh = Lang::mi_light_font_30,
                                     .en = Lang::ba_font_30,
                                     .jp = Lang::jp_font_30});

        lv_obj_align(m_middle_text.label, LV_ALIGN_CENTER, 0, -30);
    }

    void TuWaterAssist::start_routine() {
        m_input_used = true;
        m_timer = lv_timer_create(timer_cb, 5000, this);
        lv_timer_ready(m_timer);
    }

    void TuWaterAssist::routine() {
        if (!has_water)
        {
            has_water = true;
            m_current_step = 3;
            m_middle_text.update(LANG(Lang::ui_tu_water_detected));
            lv_timer_set_period(m_timer,100);
        }
    }

    void TuWaterAssist::input_cb(input_t input) {
        Base::input_cb(input);
        if (input == UI_INPUT_RIGHT) {
            m_right_touched = true;
        }
    }

    void TuWaterAssist::load_next() {
       //auto ui = UI::build_ui<TuPlantDetect>(UI::TU_PLANT_DETECT);
       //LvglDriver::instance().load(ui, true, true, true);
    }

    void TuWaterAssist::stable_cb(bool stable) {
//        static uint32_t confirm_t = millis() + 3000;
//        if (!stable || m_current_y > m_assist_bottom || m_current_y < m_assist_top) {
//            confirm_t = millis() + 3000;
//        }
//        if (millis() > confirm_t) {
//            m_right_touched = true;
//        }
    }

    void TuWaterAssist::timer_cb(lv_timer_t *timer) {
        auto ui = static_cast<TuWaterAssist *>(timer->user_data);
        ui->next();
    }

    void TuWaterAssist::next() {
        switch (m_current_step) {
            case 0: {
                std::string temp = LANG_FORMAT<int>(Lang::ui_fluid_add_about, {20});
                m_top_text.update(temp.c_str());
                break;
            }

            case 1: {
                m_bottom_text.update(Lang::Text::instance().get_text(Lang::ui_tu_water_right_next).c_str(), true, false,
                                     3000);
                set_routable_indicator_visible(true, right);
                auto a = anim_create(m_routable_indicators[right], anim_fade, LV_OPA_TRANSP,
                                     LV_OPA_COVER, 1000, 4500);
                lv_anim_set_early_apply(&a, true);
                lv_anim_start(&a);
                m_right_touched = false;
                m_middle_text.update(LANG(Lang::ui_tu_water_no_detected));
                lv_timer_set_period(m_timer,100);
                break;
            }
            case 2: {
                if (!m_right_touched) {
                    return;
                }
            }


            case 3: {
                if (has_water)
                {
                    m_bottom_text.update(Lang::Text::instance().get_text(Lang::ui_tu_water_assist_good).c_str());
                    lv_timer_set_period(m_timer,2000);
                }
                break;
            }
            case 4: {
                load_next();
                break;
            }
        }
        m_current_step++;
    }

    void TuWaterAssist::clear() {
        if (m_timer) {
            lv_timer_del(m_timer);
        }
        Base::clear();
    }

    TuPlantDetect::TuPlantDetect()
            : TuCanvasBase() {
        lv_obj_align(m_top_text.label, LV_ALIGN_TOP_MID, 0, 15);
    }

    void TuPlantDetect::next() {
        switch (m_current_step) {
            case 0: {
                m_top_text.update(Lang::Text::instance().get_text(Lang::ui_tu_plant_put_pot).c_str());
                anim_canvas_bind_asset(m_canvas, "tu/tu_ivy_2");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, -5, 10);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1500);
                lv_anim_start(&a);
                fade_indicator(right, true, 1000, 1500);
                lv_timer_set_period(m_timer, 1);
                break;
            }
            case 1: {
                if (!m_right_touched) {
                    return;
                }
                //auto ui = UI::build_ui<TuFinal>(UI::TU_FINAL);
                //LvglDriver::instance().load(ui, true, true, true);
                break;
            }
        }
        m_current_step++;
    }

    TuPlantSelect::TuPlantSelect()
            : TuCanvasBase(),
              m_middle_text(m_scr) {

        m_middle_text.set_text_font({.zh = Lang::mi_light_font_30,
                                     .en = Lang::ba_font_30,
                                     .jp = Lang::jp_font_30});

        lv_obj_align(m_middle_text.label, LV_ALIGN_CENTER, 0, -30);
        lv_obj_set_width(m_top_text.label, 280);
        lv_obj_align_to(m_top_text.label, m_middle_text.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    }

    void TuPlantSelect::next() {
        switch (m_current_step) {
            case 0: {
                m_middle_text.update(Lang::Text::instance().color_in_str(palette_notice,
                                                                         Lang::Text::instance().get_text(
                                                                                 Lang::ui_tu_plant_select_app)).c_str());
                m_top_text.update(Lang::Text::instance().get_text(Lang::ui_tu_plant_select_switch).c_str());
                fade_indicator(right, true, 1000, 4500);
                m_bottom_text.update(Lang::Text::instance().get_text(Lang::ui_tu_plant_right_skip).c_str(), true, false,
                                     3000);
                m_right_touched = false;
                lv_timer_set_period(m_timer, 1);
                break;
            }
            case 1: {
                if (!m_right_touched) {
                    return;
                }
                //LvglDriver::instance().set_locked(false);
                //LvglDriver::instance().route_to_default();
            }
        }
        m_current_step++;
    }

    TuFinal::TuFinal()
            : TuBase(),
              m_text(m_scr) {

        m_text.set_text_font({.zh = Lang::mi_light_font_30,
                              .en = Lang::ba_font_30,
                              .jp = Lang::jp_font_30});

        lv_obj_align(m_text.label, LV_ALIGN_CENTER, 0, 0);
    }

    void TuFinal::next() {
        switch (m_current_step) {
            case 0: {
                lv_timer_set_period(m_timer, 4000);
                m_text.update(Lang::Text::instance().get_text(Lang::ui_tu_congratulations).c_str());
                break;
            }
            case 1: {
                m_text.update(Lang::Text::instance().get_text(Lang::ui_tu_completed).c_str());
                break;
            }
            case 2: {
                m_text.update("");
                break;
            }
        }
        m_current_step++;
    }

    TuWaterCalib::TuWaterCalib()
            : TuBase(),
              m_step_label(m_scr, 300, 400, 300),
              m_value_label(m_scr, 300, 400, 300),
              m_desc_label(m_scr, 300, 400, 300),
              m_progress_bar(lv_bar_create(m_scr)) {

        m_step_label.set_text_font({.zh = Lang::mi_light_font_16,
                                    .en = Lang::ba_font_16,
                                    .jp = Lang::jp_font_16});
        m_value_label.set_text_font({.zh = Lang::mi_light_font_16,
                                     .en = Lang::ba_font_16,
                                     .jp = Lang::jp_font_16});
        m_desc_label.set_text_font({.zh = Lang::mi_light_font_16,
                                    .en = Lang::ba_font_16,
                                    .jp = Lang::jp_font_16});

        m_input_used = true;
        bar_set_default_style(m_progress_bar);
        lv_obj_set_size(m_progress_bar, 200, 20);

        lv_obj_align(m_step_label.label, LV_ALIGN_TOP_MID, 0, 30);
        lv_obj_align(m_value_label.label, LV_ALIGN_CENTER, 0, -20);
        lv_obj_align(m_desc_label.label, LV_ALIGN_CENTER, 0, 60);
        lv_obj_align(m_progress_bar, LV_ALIGN_CENTER, 0, 20);
    }

    void TuWaterCalib::next() {
        switch (m_current_step) {
            case 0: {
                m_step_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_calibrating).c_str());
                m_value_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_prepare_sensor).c_str());
                m_desc_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_wait_moment).c_str());
                lv_timer_set_period(m_timer, 1000);
                break;
            }
            case 1: {
                /* we need to start with no water present in the tank */
                if (m_right_touched) {
                    m_value_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_detected).c_str());
                    m_desc_label.update(
                            get_colored_str(Lang::Text::instance().get_text(Lang::ui_tu_water_tank_empty).c_str(),
                                            palette_notice).c_str());
                } else {
                    confirm_t++;
                }
                if (confirm_t < 2) {
                    return;
                }

                m_value_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_add_20_water).c_str());
                m_desc_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_continue).c_str());
                fade_indicator(right, true, 600, 0);
                m_right_touched = false;
                lv_timer_set_period(m_timer, 1);
                break;
            }
            case 2: {
                if (!m_right_touched) {
                    return;
                }
                break;
            }
            case 3: {
                if (calib_routine(20)) {
                    break;
                }
                return;
            }
            case 4: {
                if (!m_right_touched) {
                    return;
                }
                break;
            }
            case 5: {
                if (calib_routine(40)) {
                    break;
                }
                return;
            }
            case 6: {
                if (!m_right_touched) {
                    return;
                }
                break;
            }
            case 7: {
                if (calib_routine(60)) {
                    break;
                }
                return;
            }
            case 8: {
                if (!m_right_touched) {
                    return;
                }
                break;
            }
            case 9: {
                if (calib_routine(80)) {
                    break;
                }
                return;
            }
            case 10: {
                lv_timer_set_period(m_timer, 3000);
                update_progress(100);
                fade_indicator(right, false, 600, 0);
                m_value_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_calib_completed).c_str());
                m_desc_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_pour_out).c_str());
                break;
            }
            case 11: {
                //LvglDriver::instance().set_locked(false);
                //LvglDriver::instance().route_to_default();
                break;
            }
        }
        m_current_step++;

    }

    bool TuWaterCalib::calib_routine(int total_level) {
        m_value_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_analyzing).c_str());
        m_desc_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_wait_moment).c_str());
        std::string temp = LANG_FORMAT<int>(Lang::ui_tu_water_another_20_water, {total_level + 20});

        if (m_right_touched) {
            if (m_right_touched) {
                m_value_label.update(temp.c_str());
                m_desc_label.update(Lang::Text::instance().get_text(Lang::ui_tu_water_continue).c_str());
                m_right_touched = false;
                update_progress(total_level);
                return true;
            }
        } else {
            m_right_touched = false;
            m_value_label.update(temp.c_str());
            m_desc_label.update(
                    get_colored_str(Lang::Text::instance().get_text(Lang::ui_tu_water_make_sure).c_str(),
                                    palette_notice).c_str());
        }
        return false;
    }

    void TuWaterCalib::reset_progress() {
        auto *bar = (lv_bar_t *) m_progress_bar;
        bar->cur_value = 0;
    }

    void TuWaterCalib::update_progress(int progress, int anim_t) {
        if (anim_t) {
            lv_obj_set_style_anim_time(m_progress_bar, anim_t, 0);
            lv_bar_set_value(m_progress_bar, progress, LV_ANIM_ON);
            auto *bar = (lv_bar_t *) m_progress_bar;
            bar->cur_value_anim.anim_start = 0;
        } else {
            lv_bar_set_value(m_progress_bar, progress, LV_ANIM_OFF);
        }
    }

    TuApp::TuApp()
            : TuCanvasBase(),
              m_sub_text(m_scr, 280),
              m_mid_text(m_scr, 300, 800, 600) {

        m_sub_text.set_text_font({.zh = Lang::mi_light_font_16,
                                  .en = Lang::ba_font_16,
                                  .jp = Lang::jp_font_16});
        m_mid_text.set_text_font({.zh = Lang::mi_light_font_30,
                                  .en = Lang::ba_font_30,
                                  .jp = Lang::jp_font_30});
        lv_obj_align(m_mid_text.label, LV_ALIGN_CENTER, 0, -20);
        m_input_used = true;
    }

    void TuApp::next() {
        switch (m_current_step) {
            case 0:
                m_mid_text.update(LANG(Lang::ui_tu_add_app));
                lv_timer_set_period(m_timer, 3000);
                break;
            case 2: {
                m_mid_text.update("");
                m_top_text.update(LANG(Lang::ui_tu_prov_in_store));
                m_sub_text.update(LANG_COLOR(palette_notice,LANG(Lang::ui_tu_download_app)).c_str());
                lv_obj_align_to(m_sub_text.label, m_top_text.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
                anim_canvas_bind_asset(m_canvas, "tu/tu_app");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 15);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1500);
                lv_anim_start(&a);
                break;
            }
            case 3: {
                set_routable_indicator_visible(true, right);
                lv_obj_align(m_routable_indicators[1], LV_ALIGN_RIGHT_MID, -15, -20);
                auto a2 = anim_create(m_routable_indicators[1], anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1200);
                lv_anim_start(&a2);
                m_bottom_text.update(LANG(Lang::ui_tu_water_right_next));
                lv_timer_set_period(m_timer, 10);
                m_right_touched = false;
                break;
            }
            case 4: {
                if (!m_right_touched) {
                    return;
                }
                auto a = anim_create(m_routable_indicators[1], anim_fade, LV_OPA_COVER, LV_OPA_TRANSP, 500, 0);
                lv_anim_start(&a);
                m_bottom_text.update("");
                m_top_text.update(LANG(Lang::ui_in_system_setting));
                m_sub_text.update(LANG_COLOR(palette_notice,LANG(Lang::ui_enable_ble)).c_str());
                anim_canvas_change_bind(m_canvas, "tu/tu_bluetooth", 1500, 0);
                lv_timer_set_period(m_timer, 3000);
                break;
            }
            case 5: {
                auto a2 = anim_create(m_routable_indicators[1], anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1200);
                lv_anim_start(&a2);
                m_bottom_text.update(LANG(Lang::ui_touch_right_config));
                lv_timer_set_period(m_timer, 10);
                m_right_touched = false;
                break;
            }
            case 6: {
                if (!m_right_touched) {
                    return;
                }
                lv_timer_set_period(m_timer, 3000);
                break;
            }
        }
        m_current_step++;
    }
}