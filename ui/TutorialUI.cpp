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

    TuProv::TuProv() : TuCanvasBase(), m_sub_text(m_scr, &ba_16) {
        anim_canvas_bind_asset(m_canvas, "tu_app");
        anim_canvas_update(m_canvas);
        lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 30);
        lv_obj_align_to(m_sub_text.label, m_top_text.label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }

    void TuProv::next() {
        switch (m_current_step) {
            case 0:
                m_top_text.update("Now it's time to configure WiFi");
                break;
            case 1:
                m_top_text.update("In Apple Store / Play Store");
                m_sub_text.update((std::string("download ") +get_colored_str("Tuya Smart",palette_notice)
                        +get_colored_str("Esp32 SoftAP Provisioning",palette_notice)).c_str());
                m_bottom_text.update("Touch right to next step");
                break;
        }
        m_current_step++;
    }
}