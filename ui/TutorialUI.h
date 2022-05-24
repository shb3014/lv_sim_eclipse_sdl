//
// Created by Gordon on 2022/5/6.
//

#ifndef UI_SANDBOX_TUTORIALUI_H
#define UI_SANDBOX_TUTORIALUI_H

#include "Base.h"
#include "Components.h"
#include "UIFluidAssist.h"

#define TU_INTRO_DELAY      6500

namespace UI {
    class TuBase : public Base {
    public:
        TuBase();

        void start_routine() override;

        void clear() override;

        static void timer_cb(lv_timer_t *timer);

        virtual void next() = 0;

        void fade_indicator(routable_indicator_part part, bool on, uint32_t time = 1000, uint32_t delay = 0);

    protected:
        lv_timer_t *m_timer;
        int m_current_step = 0;
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

        index_t get_index() override {
            return TU_INTRO;
        }

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

        index_t get_index() override {
            return TU_TOUCH_BAR;
        }

        void next() override;

    private:
        lv_obj_t *m_circles[2] = {};
    };

    class TuProv : public TuCanvasBase {
    public:
        TuProv();

        index_t get_index() override {
            return TU_PROV;
        }

        void next() override;

    private:
        BasicText m_sub_text_a;
        BasicText m_sub_text_b;
        BasicText m_sub_text_c;

    };

    class TuTuya : public TuCanvasBase {
    public:
        TuTuya();

        index_t get_index() override {
            return TU_TUYA;
        }

        void next() override;

        void input_cb(input_t input) override;

    private:
        BasicText m_sub_text;
        bool m_left_touched = false;
    };

    class TempText : public TuBase {
    public:
        TempText();

        index_t get_index() override {
            return UI_TEMP_TEXT;
        }

        void set_text(const char *content) {
            m_target_text = content;
        }

        void set_period(uint32_t period) {
            lv_timer_set_period(m_timer, period);
        }

        void set_next_ui(index_t ui) {
            m_next_ui = ui;
        }

        void next() override;

    private:
        BasicText m_text;
        std::string m_target_text;
        index_t m_next_ui = UI_NULL;
    };

    class TuWater : public TuCanvasBase {
    public:
        TuWater();

        index_t get_index() override {
            return TU_WATER;
        }

        void input_cb(input_t input) override;

        void next() override;

    private:
        bool m_right_touched = false;
    };

    class TuWaterAssist : public UIFluidAssist {
    public:
        TuWaterAssist();

        void start_routine() override;

        void stable_cb(bool stable) override;

        uint16_t get_target_level() override {
            return 30;
        }

        uint16_t get_target_range() override {
            return 5;
        }

        static void timer_cb(lv_timer_t *timer);

        void next();

        void clear() override;

//        void input_cb(input_t input) override;
    private:
        BasicText m_bottom_text;
        lv_timer_t *m_timer = nullptr;
        int m_current_step = 0;
        bool m_right_touched = false;
    };

    class TuPlantSelect : public TuCanvasBase {
    public:
        TuPlantSelect();

        index_t get_index() override {
            return TU_PLANT;
        }

        void next() override;
    };

    class TuFinal : public TuBase {
    public:
        TuFinal();

        index_t get_index() override {
            return TU_INTRO;
        }

        void next() override;
    private:
        BasicText m_text;
    };

}


#endif //UI_SANDBOX_TUTORIALUI_H
