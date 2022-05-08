//
// Created by sungaoran on 2022/1/18.
//

#ifndef UI_SANDBOX_TOOLS_H
#define UI_SANDBOX_TOOLS_H

#include "lvgl/lvgl.h"
#include "string"
#include "utils/log.h"

namespace UI {
//#define PATH_ASSETS "C:/Users/sungaoran/Desktop/wsl/video/assets"
//#define PATH_ASSETS "C:/Users/Gordon/Desktop/EmbededProjects/lv_sim_eclipse_sdl/assets"
//#define PATH_ASSETS "D:/Ivy/device/assets/ouput"
#define PATH_ASSETS "C:/Users/sungaoran/Desktop/Ivy/out"

//region animation
    std::string get_asset_path(std::string &asset_name);

    void anim_canvas_reset_asset();

    void anim_canvas_bind_asset(lv_obj_t *canvas, std::string asset_name, bool reset = false);

    void anim_canvas_bind(lv_obj_t *canvas, const char *filepath);

    void anim_canvas_update(lv_obj_t *canvas);

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
//endregion

    void bar_set_default_style(lv_obj_t *bar);

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
}
#endif //UI_SANDBOX_TOOLS_H
