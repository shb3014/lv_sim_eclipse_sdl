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

    void UIFluid::set_amp(int amp, bool update_unit, bool update) {
        int front_amp;
        int back_amp;
        int max_amp = std::min(m_current_y, WATER_TANK_SIZE - m_current_y);
        if (amp > max_amp) amp = max_amp;
        if (amp < WATER_TANK_MIN_AMP) amp = WATER_TANK_MIN_AMP;
        if (amp > WATER_TANK_MAX_AMP) amp = WATER_TANK_MAX_AMP;
        m_current_amp = amp;
        front_amp = amp;
        if (front_amp > 4) {
            back_amp = front_amp - 2;
        } else {
            back_amp = front_amp;
        }
        m_wave_front.set_amp(front_amp, update_unit, update);
        m_wave_back.set_amp(back_amp, update_unit, update);
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

        /* add wave effect during dramatic change */
        if (m_current_y != m_last_level) {
            set_amp(m_current_amp + 1, false, false);
            m_stable_cnt = 0;
            m_last_level = m_current_y;
            /* stabilize water level when no change anymore */
        } else if (++m_stable_cnt > WATER_TANK_STABLE_UNIT_CNT) {
            set_amp(m_current_amp - 1, false, false);
            m_stable_cnt = 0;
        }
        /* update current level */
        if (m_wave_front.unit.y_offset != m_current_y) {
            m_wave_front.set_y_offset(m_current_y, true, false);
            m_wave_back.set_y_offset(m_current_y, true, false);
        } else {
            /* update unit data if the above did not */
            m_wave_front.update_unit();
            m_wave_back.update_unit();
        }
        /* add wave moving effect */
        m_wave_front.move_hor(m_current_speed);
        m_wave_back.move_hor(-1 * m_current_speed / 2);
        Base::routine();
        for (int x = 0; x < WATER_TANK_SIZE; x++) {
            uint16_t back_y = m_wave_back.data[x];
            uint16_t front_y = m_wave_front.data[x];
            for (int y = 0; y < WATER_TANK_SIZE; y++) {
                lv_color_t *pix = &m_canvas_buf[y * WATER_TANK_SIZE + x];

                /* render wave */
                if (back_y > front_y) {
                    /* back wave is blocked */
                    if (y < front_y) {
                        *pix = WATER_TANK_ENV_COLOR;
                    } else {
                        *pix = WATER_TANK_FRONT_WAVE_COLOR;
                    }
                } else {
                    /* back wave is visible */
                    if (y < back_y) {
                        *pix = WATER_TANK_ENV_COLOR;
                    } else {
                        if (y < front_y) {
                            *pix = WATER_TANK_BACK_WAVE_COLOR;
                        } else {
                            *pix = WATER_TANK_FRONT_WAVE_COLOR;
                        }

                    }
                }
            }
        }

        lv_obj_invalidate(m_canvas);
        std::string value_string = std::to_string((int) std::round(current_level)) + "mL";
//        update_bottom_label(value_string.c_str(), lv_color_white());
    }
}
