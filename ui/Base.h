//
// Created by Gordon on 2021/8/13.
//

#ifndef PLANTSIO_IVY_BASE_H
#define PLANTSIO_IVY_BASE_H

#include "lvgl/lvgl.h"
#include "vector"

namespace UI {
    typedef enum {
        UI_QUIT = -1,
        UI_NONE = 0,
        UI_PROGRESS,
        UI_DOUBLE_PROGRESS,
        UI_FLUID,
        UI_WEATHER,
        UI_TIME,
        UI_DATE,
        UI_SYS_INFO,
        UI_ACTION,
        UI_LOADING,
        UI_PLANT_STATUS,
        UI_QR,
    } index_t;

    typedef enum {
        UI_INPUT_LEFT = 0,
        UI_INPUT_RIGHT,
    } input_t;

    class UISiblings {
    public:
        explicit UISiblings(index_t left = UI_QUIT, index_t right = UI_QUIT, index_t next = UI_QUIT) : left(left),
                                                                                                       right(right),
                                                                                                       next(next) {};
        index_t left;
        index_t right;
        index_t next;
    };

    class RouterMap {
    public:
    private:
        std::vector<index_t> children;
    };

    class Base {
    public:
        /* every derived UI class shall implement its obj creation in constructor */
        Base();

        ~Base();

        /* every derived UI class must implement this method and register in the driver load method */
        virtual index_t get_index() = 0;

        /* clear animations and timers here */
        virtual void clear();

        /* called every frame */
        virtual void routine();

        /* bound to touch events */
        virtual void input_cb(input_t input);

        //region non-virtual members
        /* set ui switching behavior todo use a global ui matrix instead */
        void set_siblings(
                UISiblings siblings) {
            m_siblings = siblings;
        }


        UISiblings get_siblings() {
            return m_siblings;
        }

        void set_start(bool start = true) {
            m_start = start;
            if (start && m_scr) {
                lv_scr_load(m_scr);
                start_routine();
            }
        }

        bool started() const {
            return m_start;
        }

        lv_obj_t *get_scr() {
            return m_scr;
        }
        //endregion

    protected:
        /* animations and timers should be created and started here */
        virtual void start_routine() {}


        UISiblings m_siblings;
        lv_obj_t *m_scr;
        bool m_start = false;
    };

/* Default empty UI class */
    class UIDefault : public Base {
        using Base::Base;

        index_t get_index() override {
            return UI_NONE;
        }

        bool started() const {
            return true;
        }

    };
}
#endif //PLANTSIO_IVY_BASE_H
