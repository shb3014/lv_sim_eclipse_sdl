//
// Created by Gordon on 2022/5/26.
//

#include "UIBoot.h"
#include "tools.h"
#include "Anim/lang/Lang.h"
#include "utils/log.h"
#include "tool/sys.h"

namespace UI {
    static std::string ui_boot_desc;
    static int ui_boot_progress = 0;

    int UIBoot::get_current_progress() {
        return ui_boot_progress;
    }

    std::string UIBoot::get_current_desc() {
        return ui_boot_desc;
    }

    void UIBoot::set(const char *desc, int progress) {
        set_current_desc(desc);
        set_current_progress(progress);
    }

    void UIBoot::set_current_progress(int progress) {
        ui_boot_progress = progress;
    }

    void UIBoot::set_current_desc(const char *desc) {
        ui_boot_desc = desc;
    }

//    void UIBoot::routine() {
//        Base::routine();
//        UIProgress::update("Waking Up", get_current_desc().c_str(), get_current_progress());
//    }

    void UIBoot::start_routine() {
        Base::start_routine();
        update_title(Lang::Text::instance().get_text(Lang::ui_boot_waking_up).c_str());
        m_timer = lv_timer_create(timer_cb, 100, this);
        lv_timer_ready(m_timer);
    }

    void UIBoot::clear() {
        //Sys::set_condition(Sys::BOOT_OVER);
        if (m_timer) {
            lv_timer_del(m_timer);
        }
        Base::clear();
    }

    void UIBoot::timer_cb(lv_timer_t *timer) {
        auto ui = static_cast<UIBoot *>(timer->user_data);
        ui->next();
    }

    void UIBoot::update_now(const char *desc, int progress) {
        update_status(desc);
        update_progress(progress);
    }

    bool UIBoot::check_routine(const std::function<bool()> &check_cb, int progress, int timeout,
                               const char *success_desc, const char *fail_desc) {
        if (check_cb()) {
            update_now(success_desc, progress);
            log_d("debug-boot %s", success_desc);
            lv_timer_set_period(m_timer, 500);
            return true;
        } else {
            if (millis() - m_current_start_t > timeout) {
                update_now(get_colored_str(fail_desc, UI::palette_warning).c_str(), progress);
                log_d("debug-boot %s", fail_desc);
                lv_timer_set_period(m_timer, 800);
                return true;
            }
        }
        return false;
    }

    void UIBoot::refresh_timeout() {
        m_current_start_t = millis();
        lv_timer_set_period(m_timer, 100);
    }

    void UIBoot::next() {
        switch (m_current_step) {
            case 0: {
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_connect_to_net).c_str(),
                           5);
                refresh_timeout();
                break;
            }
            case 1:
                if (!check_routine([this]() { return m_touch_right; }, 10, 20000,
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_connect_succ).c_str(),
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_connect_fail).c_str())) {
                    return;
                }
                break;
            case 2:
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_activating).c_str(), 15);
                refresh_timeout();
                break;
            case 3:
                if (!check_routine([this]() { return m_touch_right; }, 20, 10000,
                                   Lang::Text::instance().get_text(Lang::ui_boot_activated).c_str(),
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_activate_fail).c_str())) {
                    return;
                }
                break;
            case 4:
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_tuning_time).c_str(), 25);
                refresh_timeout();
                break;
            case 5:
                if (!check_routine([this]() { return m_touch_right; }, 30, 10000,
                                   Lang::Text::instance().get_text(Lang::ui_boot_tune_succ).c_str(),
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_tune_fail).c_str())) {
                    return;
                }
                break;
            case 6:
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_locating).c_str(), 35);
                refresh_timeout();
                break;
            case 7:
                if (!check_routine([this]() { return m_touch_right; }, 40, 50000,
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_locate_succ).c_str(),
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_locate_fail).c_str())) {
                    return;
                }
                break;
            case 8:
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_physical_check).c_str(),
                           45);
                refresh_timeout();
                break;
            case 9:
                if (!check_routine([this]() { return m_touch_right; },
                                   50, 60000,
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_physical_succ).c_str(),
                                   Lang::Text::instance().get_text(
                                           Lang::ui_boot_physical_fail).c_str())) {
                    return;
                }
                break;
            case 10:
//                if (Prop::get<bool>(Prop::plant_auto_detect)) {
//                    m_plant_detect_cnt = Sense::instance().get_plant_detect_cnt();
//                    Sense::instance().set_plant_force_detect_t(millis());
//                }
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_plant_check).c_str(), 55);
                refresh_timeout();
                break;
            case 11:
//                if (Prop::get<bool>(Prop::plant_auto_detect)) {
                    if (!check_routine(
                            [this]() { return m_touch_right; },
                            60, 10000,
                            Lang::Text::instance().get_text(Lang::ui_boot_plant_checked).c_str(),
                            Lang::Text::instance().get_text(Lang::ui_boot_plant_fail).c_str())) {
                        return;
                    }
                //}
                break;
            case 12:
                lv_timer_set_period(m_timer, 500);
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_calibrating).c_str(), 80);
                break;
            case 13:
                update_now(Lang::Text::instance().get_text(Lang::ui_boot_waked_up).c_str(), 100);
                lv_timer_set_period(m_timer, 100);
                break;
            case 14:
                log_d("ui boot complete");

                /* ensure releasing of gpio holding after wake up (for auto wake up) */

//                LvglDriver::instance().set_locked(false);
//                if (Prop::get<bool>(Prop::has_pot)) {
//                    IvyAnim::instance().set_current_drv(IvyAnim::emo);
//                    EmoDriver::instance().set_current_anim(
//                            Anim::create({AnimUnit("yawn", 1)}, nullptr, true));
//                } else {
//                    LvglDriver::instance().route_to_default();
//                }
                log_d("ui boot over test");
                break;
        }
        m_current_step++;
    }

    void UIBoot::input_cb(input_t input)
    {

    }
}