//
// Created by Gordon on 2022/5/17.
//

#ifndef PLANTSIO_IVY_UIFLUID_H
#define PLANTSIO_IVY_UIFLUID_H

#include "Base.h"
#include "cmath"

#define WATER_TANK_SIZE             205
#define WATER_TANK_ENV_COLOR        lv_color_make(0,0,0)
#define WATER_TANK_VOLUME           90.0

namespace UI {

    class WaveUnit {
    public:
        /**
         * generate sine wave unit
         * @param t_amp amplitude
         * @param t_wl wave length
         * @param t_y_offset vertical offset
         */
        WaveUnit(int t_amp, int t_wl, int t_y_offset)
                : amp(t_amp),
                  wl(t_wl),
                  y_offset(t_y_offset) {
            data.reserve(t_wl);
            update_data();
        }

        void set_amp(int t_amp, bool update = true);

        void set_wl(int t_wl, bool update = true);

        void set_y_offset(int t_y_offset, bool update = true);

        std::vector<int> data;
        int amp;
        int wl;   /* wave length */
        int y_offset;

        void update_data();
    };

    class Wave {
    public:
        Wave(int t_amp, int t_wl, int t_y_offset, int t_length, int t_x_offset)
                : unit(t_amp, t_wl, t_y_offset),
                  length(t_length) {
            data.reserve(length);
            move_hor(t_x_offset);
            update_data();
        }

        void move_hor(int dis, bool update = true);

        void set_y_offset(int offset, bool update_unit = true, bool update = true) {
            unit.set_y_offset(offset, update_unit);
            if (update) {
                update_data();
            }
        }

        void update_unit() {
            unit.update_data();
        }

        void set_amp(int amp, bool update_unit = true, bool update = true) {
            unit.set_amp(amp, update_unit);
            if (update) {
                update_data();
            }
        }

        WaveUnit unit;
        std::vector<int> data;
        int length;
        int x_offset = 0;

        void update_data();
    };

    class UIFluid : public Base {
    public:
        UIFluid();

        index_t get_index() override {
            return UI_FLUID;
        }

        void routine() override;

        void set_target_y_from_percent(double percent) {
            m_target_y = (int) std::round((double) WATER_TANK_SIZE * (1 - percent));
        }

        void set_target_y(int y) {
            m_target_y = y;
        }

    private:
        std::vector<lv_color_t> m_canvas_buf;
        lv_obj_t *m_canvas;
        lv_obj_t *m_bottom_label;
        Wave m_wave_front;
        Wave m_wave_back;

        int m_target_y = 0;
        int m_current_y = WATER_TANK_SIZE;
    };
}

#endif //PLANTSIO_IVY_UIFLUID_H
