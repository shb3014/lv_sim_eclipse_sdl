//
// Created by sungaoran on 2022/1/18.
//

#ifndef UI_SANDBOX_TOOLS_H
#define UI_SANDBOX_TOOLS_H

#include <functional>
#include "lvgl/lvgl.h"
#include "string"
#include "memory"

namespace UI {
//region animation
    std::string get_asset_path(std::string &asset_name);

    void anim_canvas_reset_asset();

    void anim_canvas_bind_asset(lv_obj_t *canvas, std::string asset_name, bool reset = false);

    void anim_canvas_bind(lv_obj_t *canvas, const char *filepath);

    void anim_canvas_update(lv_obj_t *canvas);

    void anim_canvas_change_bind(lv_obj_t *canvas, std::string asset_name, uint32_t time, uint32_t delay = 0);

/**
 * basic builder of object animations
 * @param obj
 * @param exec_cb
 * @param value_start
 * @param value_end
 * @param time
 * @param delay
 * @param playback_time
 * @param playback_delay
 * @param ready_cb
 * @param user_data
 * @param path
 * @return
 */
    lv_anim_t
    anim_create(lv_obj_t *obj, lv_anim_exec_xcb_t exec_cb, int value_start, int value_end, uint32_t time,
                uint32_t delay = 0, uint32_t playback_time = 0,
                uint32_t playback_delay = 0,
                lv_anim_ready_cb_t ready_cb = nullptr,
                void *user_data = nullptr,
                int repeat_cnt = 0,
                lv_anim_path_cb_t path = lv_anim_path_ease_out);

    void anim_entrance();

    void anim_fade(void *var, int32_t value);

    void anim_move_ver(void *var, int32_t value);

    void anim_move_hor(void *var, int32_t value);

    void anim_set_align_top(void *var, int32_t value);
//endregion

//region style
/**
 * default style for bar background
 * @return
 */

    class LvDefaultStyles {
    public:
        //region Singleton
        static LvDefaultStyles &instance() {
            static std::shared_ptr<LvDefaultStyles> instance(new LvDefaultStyles());
            return *instance;
        }

        LvDefaultStyles(const LvDefaultStyles &) = delete;

        LvDefaultStyles(LvDefaultStyles &&) = delete;

        LvDefaultStyles &operator=(const LvDefaultStyles &) = delete;

        LvDefaultStyles &operator=(LvDefaultStyles &&) = delete;
        //endregion

        LvDefaultStyles();

        lv_style_t style_bar_bg{};
        lv_style_t style_bar_indic{};
    };

    void bar_set_default_style(lv_obj_t *bar);

    void line_set_style(lv_obj_t *line, lv_coord_t width, lv_color_t color, bool is_rounded = true);

//endregion


    void ui_set_action(bool apply);

    typedef enum {
        palette_success,
        palette_notice,
        palette_warning,
        palette_failure,
    } palette_t;

    lv_color_t get_palette_rgb(palette_t palette);

    std::string get_palette_hex(palette_t palette);

    std::string get_colored_str(const char *content, palette_t palette);

    void label_set_style(lv_obj_t *label, const lv_font_t *font, lv_color_t color = lv_color_white(),
                         lv_text_align_t align = LV_TEXT_ALIGN_CENTER);

    void show_temp_text(const char *text, uint32_t period = 3000);

    void ui_confirm(const char *title, const char *desc, const std::function<void()> &apply_cb,
                    const std::function<void()> &cancel_cb = nullptr, bool *processing_flag = nullptr, int timeout = 30);
}
#endif //UI_SANDBOX_TOOLS_H
