//
// Created by Gordon on 2022/5/17.
//

#include "UIFluid.h"
#include "tools.h"

namespace UI {
    void WaveUnit::update_data() {
        data.resize(wl);
//        double k = 2 * PI / (double) wl;
        double k = 2 * 3.1415926535897932384626433832795 / (double) wl;
        for (int x = 0; x < wl; x++) {
            data[x] = (int) round((double) amp * sin(k * (double) x)) + y_offset;
        }
    }

    void WaveUnit::set_amp(int t_amp, bool update) {
        amp = t_amp;
        if (update) {
            update_data();
        }
    }

    void WaveUnit::set_wl(int t_wl, bool update) {
        wl = t_wl;
        if (update) {
            update_data();
        }
    }

    void WaveUnit::set_y_offset(int t_y_offset, bool update) {
        y_offset = t_y_offset;
        if (update) {
            update_data();
        }
    }

    void Wave::update_data() {
        /* copy the last _t of a unit */
        data.clear();
        data.reserve(length);
        std::copy(unit.data.begin() + unit.wl - x_offset, unit.data.end(), std::back_inserter(data));
        int n = x_offset;
        while (length - n > unit.wl) {
            std::copy(unit.data.begin(), unit.data.end(), std::back_inserter(data));
            n += unit.wl;
        }
        std::copy(unit.data.begin(), unit.data.begin() + length - n, std::back_inserter(data));
    }

    void Wave::move_hor(int dis, bool update) {
        dis = dis % unit.wl;
        x_offset += dis;
        x_offset = x_offset % unit.wl;
        if (x_offset < 0) {
            x_offset = unit.wl + x_offset;
        }
        if (update) {
            update_data();
        }
    }

    UIFluid::UIFluid()
            : Base(),
              m_canvas(lv_canvas_create(m_scr)),
              m_bottom_label(lv_label_create(m_scr)),
              m_wave_front(10, 150, 10, WATER_TANK_SIZE, 0),
              m_wave_back(6, 120, 10, WATER_TANK_SIZE, 3) {
        m_canvas_buf.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR(WATER_TANK_SIZE, WATER_TANK_SIZE));
        lv_canvas_set_buffer(m_canvas, m_canvas_buf.data(), WATER_TANK_SIZE, WATER_TANK_SIZE, LV_IMG_CF_TRUE_COLOR);
        lv_obj_align(m_canvas, LV_ALIGN_CENTER, 0, 0);
        lv_canvas_fill_bg(m_canvas, WATER_TANK_ENV_COLOR, LV_OPA_COVER);

        label_set_style(m_bottom_label, &ba_30);
    }

    void UIFluid::routine() {
        double current_level = 60.0;/* fixme */
        set_target_y_from_percent(current_level / WATER_TANK_VOLUME);
        if (m_current_y < m_target_y) {
            /* dropping */
            m_current_y += (m_target_y - m_current_y) / 5 + 1;
        } else if (m_current_y > m_target_y) {
            /* rising */
            m_current_y -= (m_current_y - m_target_y) / 5 + 1;
        }

        Base::routine();
    }
}
