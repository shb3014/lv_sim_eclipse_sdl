//
// Created by Gordon on 2022/5/6.
//

#ifndef UI_SANDBOX_TUTORIALUI_H
#define UI_SANDBOX_TUTORIALUI_H

#include "Base.h"
#include "Components.h"
#include "UIFluidAssist.h"

#define TU_INTRO_DELAY      6000

namespace UI {
    class TuBase : public Base {
    public:
        TuBase();

        void start_routine() override;

        void clear() override;

        static void timer_cb(lv_timer_t *timer);

        virtual void next() = 0;

        void fade_indicator(routable_indicator_part part, bool on, uint32_t time = 1000, uint32_t delay = 0);

        void input_cb(input_t input) override;

    protected:
        lv_timer_t *m_timer = nullptr;
        int m_current_step = 0;
        bool m_right_touched = false;
        bool m_left_touched = false;
    };

    class TuCanvasBase : public TuBase {
    public:
        TuCanvasBase();

    protected:
        lv_obj_t *m_canvas;
        BasicText m_top_text;
        BasicText m_bottom_text;
    };

    class TuIntro : public TuBase {
    public:
        explicit TuIntro();

        void next() override;

    private:
        void update(const char *main, const char *sub);

        void update_main(const char *main);

        void update_sub(const char *sub);

        void realign() const;

        BasicText m_top_text;
        BasicText m_bottom_text;
    };

    class TuTouchBar : public TuCanvasBase {
    public:
        TuTouchBar();

        void next() override;

    private:
        lv_obj_t *m_circles[2] = {};
    };

    class TuProvFail : public TuBase {
    public:
        TuProvFail();

        void next() override;

        void start_routine() override;

    private:
        BasicText m_text;
    };

    class TuApp : public TuCanvasBase {
    public:
        TuApp();

        void next() override;

    private:
        BasicText m_sub_text;
        BasicText m_mid_text;
    };

    class TempText : public TuBase {
    public:
        TempText();

        void start_routine() override;

        void set_text(const char *content) {
            m_target_text = content;
        }

        void set_period(uint32_t period) {
            m_period = period;
        }

        void set_next_ui(index_t ui) {
            m_next_ui = ui;
        }

        void next() override;

    private:
        BasicText m_text;
        std::string m_target_text;
        index_t m_next_ui = UI_NULL;
        uint32_t m_period = 2000;
    };

    class TuWater : public TuCanvasBase {
    public:
        TuWater();

        void next() override;
    };

    class TuWaterAssist : public TuCanvasBase {
    public:
        TuWaterAssist();

        void start_routine() override;

        void routine() override;

        void stable_cb(bool stable);

        static void timer_cb(lv_timer_t *timer);

        void next();

        void clear() override;

        void input_cb(input_t input) override;

    private:
        static void load_next();

        lv_timer_t *m_timer = nullptr;
        int m_current_step = 0;
        bool m_right_touched = false;
        bool has_water = false;
        BasicText m_middle_text;
    };


    class TuPlantDetect : public TuCanvasBase {
    public:
        TuPlantDetect();

        void next() override;
    };

    class TuPlantSelect : public TuCanvasBase {
    public:
        TuPlantSelect();

        void next() override;

    private:
        BasicText m_middle_text;
    };

    class TuFinal : public TuBase {
    public:
        TuFinal();

        void next() override;

    private:
        BasicText m_text;
    };

    class TuWaterCalib : public TuBase {
    public:
        TuWaterCalib();

        void next() override;

        bool calib_routine(int total_level);

        void update_progress(int progress, int anim_t = 0);

        void reset_progress();

    private:
        BasicText m_step_label;
        BasicText m_value_label;
        BasicText m_desc_label;
        lv_obj_t *m_progress_bar;
        int confirm_t = 0;
    };
}


#endif //UI_SANDBOX_TUTORIALUI_H
