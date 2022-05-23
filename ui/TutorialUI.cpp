//
// Created by Gordon on 2022/5/6.
//

#include "TutorialUI.h"
#include "tools.h"

#ifdef Ivy

#include "memory"
#include "Anim/drivers/LvglDriver.h"

#endif

namespace UI {

    //region TuBase
    TuBase::TuBase()
            : m_timer(lv_timer_create(timer_cb, TU_INTRO_DELAY, this)) {}

    void TuBase::start_routine() {
        Base::start_routine();
        lv_timer_ready(m_timer);
    }

    void TuBase::clear() {
        lv_timer_del(m_timer);
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
              m_top_text(m_scr, &ba_30),
              m_bottom_text(m_scr, &ba_16) {
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
                update("Hi", "");
                break;
            case 1:
                update_main("I'm Ivy");
                break;
            case 2:
                update_main("Nice to meet you");
                break;
            case 3:
                update_main("Before we enter tutorial");
                break;
            case 4:
                update_main("Please make sure the plant is ready");
                break;
            case 5:
                update_sub((UI::get_colored_str("Otherwise", UI::palette_warning) +
                            ", please shutdown by long pressing the back button").c_str());
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
        anim_canvas_bind_asset(m_canvas, "tu_ivy");
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
        switch (m_current_step++) {
            case 0:
                m_top_text.update("There are two touch bars");
                lv_timer_set_period(m_timer, 3000);
                break;
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
                m_top_text.update((get_colored_str("Yellow", palette_notice) + " dots imply intractable bars").c_str());
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
                m_bottom_text.update("Now, let's try touch the left bar");
                auto a = anim_create(m_routable_indicators[0], anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1500, 2000);
                lv_anim_start(&a);
                break;
            }
            case 5: {
                while (true) {
                    printf("wait...\n");
                }
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
        anim_canvas_bind_asset(m_canvas, "tu_app");
        anim_canvas_update(m_canvas);
        lv_obj_add_flag(m_canvas, LV_OBJ_FLAG_HIDDEN);
        lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 30);
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
                m_bottom_text.update("Touch right to next step");
                lv_obj_set_style_opa(m_canvas, LV_OPA_TRANSP, 0);
                lv_obj_clear_flag(m_canvas, LV_OBJ_FLAG_HIDDEN);
                auto a = anim_create(m_canvas, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 1000, 1000);
                lv_anim_start(&a);
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
                lv_timer_set_period(m_timer, 4000);
                break;
            }
            case 2: {
                fade_indicator(right, true);
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

    TuWaterAssist::TuWaterAssist() : UIFluidAssist(150) {
        lv_obj_align(m_bottom_label, LV_ALIGN_CENTER, 0, 30);

    }
}