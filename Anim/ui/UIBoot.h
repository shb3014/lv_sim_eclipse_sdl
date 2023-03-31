//
// Created by Gordon on 2022/5/26.
//

#ifndef PLANTSIO_IVY_UIBOOT_H
#define PLANTSIO_IVY_UIBOOT_H

#include <functional>
#include <string>

#include "UIProgress.h"

namespace UI {
    class UIBoot : public UIProgress {
    public:
        static void set(const char *desc, int progress);

        void update_now(const char *desc, int progress);

        bool check_routine(const std::function<bool()> &check_cb, int progress, int timeout, const char *success_desc,
                           const char *fail_desc);

        static int get_current_progress();

        static void set_current_progress(int progress);

        static std::string get_current_desc();

        static void set_current_desc(const char *desc);

//        void routine() override;

        void start_routine() override;

        void clear() override;

        static void timer_cb(lv_timer_t *timer);

        void next();

        void input_cb(input_t input) override;

    private:
        void refresh_timeout();

        lv_timer_t *m_timer = nullptr;
        int m_current_step = 0;
        uint32_t m_current_start_t = 0;

        uint32_t m_plant_detect_cnt = 0;

        bool m_touch_right = false;
    };
}


#endif //PLANTSIO_IVY_UIBOOT_H
