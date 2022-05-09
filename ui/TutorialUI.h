//
// Created by Gordon on 2022/5/6.
//

#ifndef UI_SANDBOX_TUTORIALUI_H
#define UI_SANDBOX_TUTORIALUI_H

#include "Base.h"
#include "Components.h"

#define TU_INTRO_DELAY      6500

namespace UI {
    class TuBase : public Base {
    public:
        TuBase();

        void start_routine() override;

        void clear() override;

        static void timer_cb(lv_timer_t *timer);

        virtual void next() = 0;

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
    };
}


#endif //UI_SANDBOX_TUTORIALUI_H
