//
// Created by Gordon on 2021/8/13.
//

#ifndef PLANTSIO_IVY_BASE_H
#define PLANTSIO_IVY_BASE_H

#include "lvgl/lvgl.h"
#include "vector"

namespace UI {
    typedef enum {
        UI_NULL = -1,
        UI_QUIT = 0,
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
        UI_TEST,
        UI_TEXT,

        TU_INTRO,
        TU_TOUCH_BAR,
        TU_PROV
    } index_t;

    typedef enum {
        UI_INPUT_LEFT = 0,
        UI_INPUT_RIGHT,
    } input_t;

    typedef struct {
        index_t index_ui;
        int index_main;
        int index_sub;
    } RoutableTarget;

    typedef enum {
        left = 0,
        right,
        all,
    } routable_indicator_part;

    /* note this is not thread safe */
    class RouterMap {
    public:
        RouterMap(std::initializer_list<std::vector<index_t>> map) : m_map(map) {}

        RoutableTarget get_main_next(int current_main) {
            int target_main;
            if (current_main + 1 < get_main_size()) {
                target_main = current_main + 1;
            } else {
                target_main = 0;
            }
            return {m_map[target_main][0], target_main, 0};
        }

        RoutableTarget get_sub_left(int current_main, int current_sub) {
            auto &sub = m_map[current_main];
            int target_sub;
            if (current_sub > 0) {
                target_sub = current_sub - 1;
            } else {
                target_sub = sub.size() - 1;
            }
            return {sub[target_sub], current_main, target_sub};
        }

        RoutableTarget get_sub_right(int current_main, int current_sub) {
            auto &sub = m_map[current_main];
            int target_sub;
            if (current_sub + 1 < sub.size()) {
                target_sub = current_sub + 1;
            } else {
                target_sub = 0;
            }
            return {sub[target_sub], current_main, target_sub};
        }

        index_t get_first() {
            return m_map[0][0];
        }

        size_t get_main_size() {
            return m_map.size();
        }

        size_t get_sub_size(unsigned index_main) {
            if (index_main < m_map.size()) {
                return m_map[index_main].size();
            } else {
                return 0;
            }
        }

    private:
        std::vector<std::vector<index_t>> m_map;
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

        bool input_used() const {
            return m_input_used;
        }

        void set_input_used(bool used) {
            m_input_used = true;
            if (used) {
                set_routable_indicator_visible(true);
            }
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

        void set_routable_indicator_visible(bool visible, routable_indicator_part part = all);

        void set_router(RouterMap *map, int main, int sub) {
            m_map = map;
            m_router_main = main;
            m_router_sub = sub;
            if (left_right_routable()) {
                set_routable_indicator_visible(true);
            }
        }

        RouterMap *get_router_map() {
            return m_map;
        }

        bool routable() {
            return get_router_map();
        }

        bool left_right_routable() {
            return routable() && get_router_map()->get_sub_size(m_router_main) > 1;
        }

        RoutableTarget get_ui_next() {
            if (m_map) {
                return m_map->get_main_next(m_router_main);
            } else {
                return {UI_NULL, 0, 0};
            }
        }

        RoutableTarget get_ui_left() {
            if (m_map) {
                return m_map->get_sub_left(m_router_main, m_router_sub);
            } else {
                return {UI_NULL, 0, 0};
            }
        }

        RoutableTarget get_ui_right() {
            if (m_map) {
                return m_map->get_sub_right(m_router_main, m_router_sub);
            } else {
                return {UI_NULL, 0, 0};
            }
        }


    protected:
        /* animations and timers should be created and started here */
        virtual void start_routine() {}

        lv_obj_t *m_scr;
        bool m_start = false;
        bool m_input_used = false;  /* note should be set to true if input_cb is implemented */
        RouterMap *m_map = nullptr;
        int m_router_main = 0;
        int m_router_sub = 0;

        lv_obj_t *m_routable_indicators[2] = {};
    };

/* Default empty UI class */
    class UIDefault : public Base {
    public:
        using Base::Base;

        index_t get_index() override {
            return UI_QUIT;
        }

        bool started() const {
            return true;
        }

    };
}
#endif //PLANTSIO_IVY_BASE_H
