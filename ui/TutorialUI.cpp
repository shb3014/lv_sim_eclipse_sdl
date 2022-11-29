//
// Created by Gordon on 2022/5/6.
//

#include "TutorialUI.h"
#include "tools.h"

#include "font/AddFontRT.h"

#ifdef Ivy

#include "memory"
#include "Anim/drivers/LvglDriver.h"

#endif

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
    //endregion

    TuCanvasBase::TuCanvasBase()
            : TuBase(),
              m_top_text(m_scr, &ba_16, 250),
              m_bottom_text(m_scr, &ba_16, 250) {

        m_canvas = lv_canvas_create(m_scr);
        anim_canvas_reset_asset();

        lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 0);
        lv_obj_align(m_top_text.label, LV_ALIGN_TOP_MID, 0, 20);
        lv_obj_align(m_bottom_text.label, LV_ALIGN_BOTTOM_MID, 0, -20);
    }

    //region intro
    TuIntro::TuIntro()
            : TuBase(),
              m_top_text(m_scr, CNFont::instance().get_font()),
              m_bottom_text(m_scr, CNFont::instance().get_font()) {
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
                //update("Hi", "");
                update("您好!", "");
                break;
            case 1:
                //update_main("I'm Ivy");
                update_main("我叫艾薇!");
                break;
            case 2:
                //update_main("Nice to meet you");
                update_main("我很好高兴见到你!");
                break;
            case 3:
                //update_main("Before we enter tutorial");
                update_main("我们开始指导教程之前,");
                break;
            case 4:
                //update_main("Please make sure the plant is ready");
                update_main("请您确认植物已经准备好.");
                break;
            case 5:
//                update_sub((UI::get_colored_str("Otherwise", UI::palette_warning) +
//                            ", please shutdown by long pressing the back button").c_str());
                update_sub((UI::get_colored_str("否则", UI::palette_warning) +
                            ", 请按我背后电源键关机!!").c_str());
                break;
            case 6:
                update("", "");
                break;
            case 7:
#ifdef Ivy
                auto ui = std::make_shared<TuTouchBar>();
                LvglDriver::instance().load(ui);
#endif
                break;
        }
    }
    //endregion

    TuTouchBar::TuTouchBar() : TuCanvasBase() {
        m_input_used = true;
        anim_canvas_bind_asset(m_canvas, "tu/tu_ivy");
        anim_canvas_update(m_canvas);


        m_top_text.update("Interact using the two touch bars");
        for (auto &circle: m_circles) {
            circle = lv_arc_create(m_scr);
//            lv_arc_set_value(circle, 40);
//            lv_obj_set_style_opa(circle,LV_OPA_TRANSP,LV_PART_KNOB);
//            lv_obj_set_style_opa(circle,LV_OPA_TRANSP,LV_PART_MAIN);
//            lv_obj_add_flag(circle, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_size(circle, 50, 50);
            lv_obj_set_style_arc_width(circle, 2, 0);
            lv_obj_set_style_arc_width(circle, 2, LV_PART_INDICATOR);
            lv_arc_set_rotation(circle, 0);
            lv_arc_set_value(circle, 0);
            lv_arc_set_bg_angles(circle, 0, 0);
            lv_obj_set_style_arc_color(circle, get_palette_rgb(palette_failure), 0);
//            lv_obj_set_style_arc_color(circle, lv_color_make(200, 200, 200), LV_PART_INDICATOR);
            lv_obj_remove_style(circle, NULL, LV_PART_KNOB);
            lv_obj_clear_flag(circle, LV_OBJ_FLAG_CLICKABLE);
        }
        lv_obj_align(m_circles[0], LV_ALIGN_CENTER, -80, 10);
        lv_obj_align(m_circles[1], LV_ALIGN_CENTER, 80, 10);
    }

    void TuTouchBar::next() {
        switch (m_current_step) {
            case 0: {
                m_top_text.update("There are two touch bars");
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
                m_top_text.update((get_colored_str("Yellow", palette_notice) + " dots imply interactive bars").c_str());
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
                lv_timer_set_period(m_timer, 10);
                m_bottom_text.update("Now, let's try touch the left bar");
                fade_indicator(left, false, 1000, 2000);
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                printf("here...\n");
                break;
            }
        }

    }

    TuProv::TuProv()
            : TuCanvasBase(),
              m_sub_text_a(m_scr, &ba_16, 80),
              m_sub_text_b(m_scr, &ba_16, 210),
              m_sub_text_c(m_scr, &ba_30, 10) {
        m_input_used = true;
    }

    void TuProv::next() {
        switch (m_current_step) {
            case 0:
                m_top_text.update("Now it's time to configure WiFi");
                break;
            case 1: {
                m_top_text.update("In Apple Store / Play Store");
                m_sub_text_a.update("download");
                m_sub_text_b.update("Esp32 SoftAP Provisioning\nTuya Smart");
                lv_obj_set_style_text_color(m_sub_text_b.label, get_palette_rgb(palette_notice), 0);
                lv_obj_set_style_text_align(m_sub_text_b.label, LV_TEXT_ALIGN_LEFT, 0);
                m_sub_text_c.update("{");
                lv_obj_align_to(m_sub_text_a.label, m_top_text.label, LV_ALIGN_OUT_BOTTOM_MID, -108, 30);
                lv_obj_align_to(m_sub_text_b.label, m_top_text.label, LV_ALIGN_OUT_BOTTOM_MID, 55, 15);
                lv_obj_align_to(m_sub_text_c.label, m_sub_text_a.label, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
                lv_obj_set_style_text_line_space(m_sub_text_b.label, 10, 0);
                anim_canvas_bind_asset(m_canvas, "tu/tu_app");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 30);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1000);
                lv_anim_start(&a);
                lv_timer_set_period(m_timer, 3000);
                break;
            }
            case 2: {
                set_routable_indicator_visible(true, right);
                lv_obj_align(m_routable_indicators[1], LV_ALIGN_RIGHT_MID, -15, -20);
                auto a2 = anim_create(m_routable_indicators[1], anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1000);
                lv_anim_start(&a2);
                break;
            }
        }
        m_current_step++;
    }

    TuTuya::TuTuya()
            : TuCanvasBase(),
              m_sub_text(m_scr, &ba_16, 280) {
        m_input_used = true;
    }

    void TuTuya::next() {
        switch (m_current_step) {
            case 0: {
                m_top_text.update("Good! Let's now move to activation");
                break;
            }
            case 1: {
                m_top_text.update((std::string("Open ") + get_colored_str("Tuya Smart", palette_notice)).c_str());
                m_sub_text.update((std::string("Click ") + get_colored_str("Add Device", palette_notice) +
                                   " at the top right").c_str());
                lv_obj_align_to(m_sub_text.label, m_top_text.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
//                lv_obj_set_style_text_line_space(m_top_text.label, 8, 0);
                anim_canvas_bind_asset(m_canvas, "tu_tuya_1");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 10);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1500);
                lv_anim_start(&a);
                set_routable_indicator_visible(true, right);
                auto a2 = anim_create(m_routable_indicators[1], anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1000);
                lv_anim_start(&a2);
                lv_timer_set_period(m_timer, 3000);
                break;
            }
            case 2: {
                m_bottom_text.update("Touch right to the next step");
                lv_timer_set_period(m_timer, 5000);
                break;
            }
            case 3: {
                m_bottom_text.update("Touch right to the next step", true, true);
                m_sub_text.update((std::string("Click the ") + get_colored_str("scan icon", palette_notice) +
                                   " at the top right").c_str());
                anim_canvas_change_bind(m_canvas, "tu_tuya_2", 1500);
                break;
            }
            case 4: {
//                m_top_text.update()
                break;
            }
        }
        m_current_step++;
    }

    void TuTuya::input_cb(input_t input) {
        Base::input_cb(input);
    }

    TempText::TempText()
            : TuBase(),
              m_text(m_scr, &ba_16) {
        lv_obj_set_align(m_text.label, LV_ALIGN_CENTER);
    }

    void TempText::next() {
        switch (m_current_step) {
            case 0:
                m_text.update(m_target_text.c_str());
                break;
            case 2: {
                m_text.update("");
            }
            case 3: {
#ifdef Ivy
                if (m_next_ui == UI_NULL) {
                    LvglDriver::instance().route_to_default();
                } else {
                    LvglDriver::instance().load(m_next_ui);
                }
#else
                if (m_next_ui == UI_NULL) {
                    break;
                } else {
                    auto ui = std::make_shared<TuWater>();
                    ui->set_start(true);
                }
#endif
            }
        }
        m_current_step++;
    }

    TuWater::TuWater() : TuCanvasBase() {
        m_input_used = true;
        lv_obj_align(m_top_text.label, LV_ALIGN_TOP_MID, 0, 15);
    }

    void TuWater::next() {
        switch (m_current_step) {
            case 0: {
                m_top_text.update("Nice! Let's now prepare for the plant");
                lv_timer_set_period(m_timer, 4500);
                break;
            }
            case 1: {
                m_top_text.update(get_colored_str("Remove the pot before adding water", palette_notice).c_str());
//                m_top_text.update("Please add 20mL of Water")
                anim_canvas_bind_asset(m_canvas, "tu/tu_water");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, -5, 10);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1500);
                lv_anim_start(&a);
                break;
            }
            case 2: {
                m_top_text.update("Touch right to the next step");
                fade_indicator(right, true, 1000, 1500);
                lv_timer_set_period(m_timer, 1);
                m_right_touched = false;
                break;
            }
            case 3: {
                if (!m_right_touched) {
                    return;
                }

            }
        }
        m_current_step++;
    }

    void TuWater::input_cb(input_t input) {
        Base::input_cb(input);
        if (input == UI_INPUT_RIGHT) {
            m_right_touched = true;
        }
    }

    TuWaterAssist::TuWaterAssist()
            : UIFluidAssist(150),
              m_bottom_text(m_scr, &ba_16) {
        lv_obj_align(m_bottom_label, LV_ALIGN_CENTER, 0, 30);
        lv_obj_align(m_middle_label, LV_ALIGN_CENTER, 0, -10);
        lv_obj_align(m_bottom_text.label, LV_ALIGN_BOTTOM_MID, 0, -20);
    }

    void TuWaterAssist::start_routine() {
        UIFluidAssist::start_routine();
        m_timer = lv_timer_create(timer_cb, 5000, this);
        lv_timer_ready(m_timer);
    }

    void TuWaterAssist::stable_cb(bool stable) {
        UIFluidAssist::stable_cb(stable);
        if (stable && m_current_y <= m_assist_bottom && m_current_y >= m_assist_top) {
            m_right_touched = true;
        }
    }

    void TuWaterAssist::timer_cb(lv_timer_t *timer) {
        auto ui = static_cast<TuWaterAssist *>(timer->user_data);
        ui->next();
    }

    void TuWaterAssist::next() {
        switch (m_current_step) {
            case 0: {
                m_bottom_text.update("Touch right to the next step", true, false, 2000);
                set_routable_indicator_visible(true, right);
                auto a = anim_create(m_routable_indicators[right], anim_fade, LV_OPA_TRANSP,
                                     LV_OPA_COVER, 1000, 3500);
                lv_anim_set_early_apply(&a, true);
                lv_anim_start(&a);
                lv_timer_set_period(m_timer, 1);
                m_right_touched = false;
                break;
            }
            case 1: {
                if (!m_right_touched) {
                    return;
                }
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
                m_top_text.update("Now put the inner-pot in");
                anim_canvas_bind_asset(m_canvas, "tu/tu_ivy_2");
                anim_canvas_update(m_canvas);
                lv_obj_align(m_canvas, LV_ALIGN_CENTER, -5, 10);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1500);
                lv_anim_start(&a);
                fade_indicator(right, true, 1000, 1500);
                lv_timer_set_period(m_timer, 1);
                break;
            }
        }
        m_current_step++;
    }

    TuPlantSelect::TuPlantSelect()
            : TuCanvasBase(),
              m_middle_text(m_scr, &ba_30) {
        lv_obj_align(m_middle_text.label, LV_ALIGN_CENTER, 0, -30);
        lv_obj_set_width(m_top_text.label, 280);
        lv_obj_align_to(m_top_text.label, m_middle_text.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    }

    void TuPlantSelect::next() {
        switch (m_current_step) {
            case 0: {
                m_middle_text.update(
                        ("Please select your plant in " + get_colored_str("Tuya APP", palette_notice)).c_str());

                m_top_text.update("After the plant is selected,\nthis page will be automatically switched.");
                fade_indicator(right, true, 1000, 4500);
                m_bottom_text.update("Or touch right to skip", true, false, 3000);
//                m_right_touched = false;
                break;
            }
//            case 1: {
//                if (!Prop::get<bool>(Prop::plant_type) && !m_right_touched) {
//                    return;
//                }
//            }
        }
        m_current_step++;
    }

    TuFinal::TuFinal()
            : TuBase(),
              m_text(m_scr, &ba_30) {
        lv_obj_align(m_text.label, LV_ALIGN_CENTER, 0, 0);
    }

    void TuFinal::next() {
        switch (m_current_step) {
            case 0: {
                lv_timer_set_period(m_timer, 4000);
                m_text.update("Congratulations!");
                break;
            }
            case 1: {
                m_text.update("You have completed the tutorial!");
                break;
            }
            case 2: {
                break;
            }
        }
        m_current_step++;
    }

    TuWaterCalib::TuWaterCalib()
            : TuBase(),
              m_step_label(m_scr, &ba_30, 300, 400, 300),
              m_value_label(m_scr, &ba_16, 300, 400, 300),
              m_desc_label(m_scr, &ba_16, 300, 400, 300),
              m_progress_bar(lv_bar_create(m_scr)) {
        bar_set_default_style(m_progress_bar);
        lv_obj_set_size(m_progress_bar, 200, 20);

        lv_obj_align(m_step_label.label, LV_ALIGN_TOP_MID, 0, 30);
        lv_obj_align(m_value_label.label, LV_ALIGN_CENTER, 0, -20);
        lv_obj_align(m_desc_label.label, LV_ALIGN_CENTER, 0, 60);
        lv_obj_align(m_progress_bar, LV_ALIGN_CENTER, 0, 20);
        m_step_label.update("Calibrating Level Sensor");

//        m_value_label.update("Preparing sensor environment...");
//        m_desc_label.update("Please wait for a moment");

//        m_value_label.update("Detected water presence.");
//        m_desc_label.update(get_colored_str("Please make sure the tank is empty.", palette_notice).c_str());

//        m_value_label.update("Please add 20mL of water.");
//        m_desc_label.update("After the water is added\nplease touch the right pad to continue.");

//        m_value_label.update("Please add 20mL of water.");
//        m_desc_label.update(
//                get_colored_str("Please make sure the water is added.", palette_notice).c_str());


        m_value_label.update("Now add another 20mL of water\n(40mL in total).");
        m_desc_label.update("After the water is added\nplease touch the right pad to continue.");

    }

    void TuWaterCalib::next() {

    }
}