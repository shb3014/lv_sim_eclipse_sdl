//
// Created by sungaoran on 2022/1/18.
//

#include "tools.h"

#include <utility>
#include "drivers/QoiCodec.h"
#include "ui/UIActionBox.h"
#include "drivers/common.h"

namespace UI {
    static void decode_to_canvas_cb(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data) {
        /* assume x===0 */
        int ptr = w * y;
        memcpy(get_canvas_buf() + ptr, data, w * h * sizeof(uint16_t));
    }

    std::string current_asset;

    void anim_canvas_reset_asset() {
        current_asset = "";
    }

    void anim_canvas_bind_asset(lv_obj_t *canvas, std::string asset_name, bool reset) {
        if (reset || current_asset != asset_name) {
            current_asset = asset_name;
            anim_canvas_bind(canvas, get_asset_path(asset_name).c_str());
        }
    }

    void anim_canvas_bind(lv_obj_t *canvas, const char *filepath) {
        QoiCodec &qoi = QoiCodec::instance();
        if (qoi.decode_video(filepath, &decode_to_canvas_cb)) {
            uint16_t w = qoi.get_current_desc().width;
            uint16_t h = qoi.get_current_desc().height;
            lv_canvas_set_buffer(canvas, get_canvas_buf(), w, h, LV_IMG_CF_TRUE_COLOR);
        } else {
            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            lv_canvas_draw_text(canvas, 0, 0, 50, &label_dsc, "not found");
        }
    }

    void anim_canvas_update(lv_obj_t *canvas) {
        if (QoiCodec::instance().decode_video_routine()) {
            lv_obj_invalidate(canvas);
        }
    }

    static void _anim_canvas_change_bind_cb(struct _lv_anim_t *anim) {
        anim_canvas_bind_asset((lv_obj_t *) anim->var, current_asset, true);
        anim_canvas_update((lv_obj_t *) anim->var);
        auto a = anim_create((lv_obj_t *) anim->var, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, anim->time);
        lv_anim_start(&a);
    }

    void anim_canvas_change_bind(lv_obj_t *canvas, std::string asset_name, uint32_t time, uint32_t delay) {
        current_asset = std::move(asset_name);
        auto a = anim_create(canvas, anim_fade, LV_OPA_COVER, LV_OPA_TRANSP, time, delay, 0, 0,
                             _anim_canvas_change_bind_cb);
        lv_anim_start(&a);
    }

    std::string get_asset_path(std::string &asset_name) {
        return std::string(PATH_ASSETS) + "/" + asset_name + ".mqoi";
    }

    lv_anim_t
    anim_create(lv_obj_t *obj, lv_anim_exec_xcb_t exec_cb, int value_start, int value_end, uint32_t time,
                uint32_t delay,
                uint32_t playback_time, uint32_t playback_delay,
                lv_anim_ready_cb_t ready_cb, void *user_data, int repeat_cnt, lv_anim_path_cb_t path) {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_exec_cb(&a, exec_cb);
        lv_anim_set_values(&a, value_start, value_end);
        lv_anim_set_time(&a, time);
        if (delay) {
            lv_anim_set_delay(&a, delay);
        }
        if (playback_time) {
            lv_anim_set_playback_time(&a, playback_time);
            lv_anim_set_playback_delay(&a, playback_delay);
        }
        lv_anim_set_path_cb(&a, path);
        lv_anim_set_ready_cb(&a, ready_cb);
        lv_anim_set_user_data(&a, user_data);
        lv_anim_set_repeat_count(&a, repeat_cnt);
        return a;
    }

    void anim_fade(void *var, int32_t value) {
        lv_obj_set_style_opa((lv_obj_t *) var, value, 0);
    }

    void anim_move_ver(void *var, int32_t value) {
        lv_obj_set_y((lv_obj_t *) var, value);
    }

    void anim_move_hor(void *var, int32_t value) {
        lv_obj_set_x((lv_obj_t *) var, value);
    }

    void anim_set_align_top(void *var, int32_t value) {
        lv_obj_align((lv_obj_t *) var, LV_ALIGN_TOP_MID, 0, value);
    }

//region style
    lv_color_t get_palette_rgb(palette_t palette) {
        static const lv_color_t colors[] = {
                LV_COLOR_MAKE(52, 192, 0), LV_COLOR_MAKE(245, 203, 38), LV_COLOR_MAKE(255, 153, 102),
                LV_COLOR_MAKE(219, 0, 0)
        };
        return colors[palette];
    }

    std::string get_palette_hex(palette_t palette) {
        static const std::string colors[] = {
                "34c000", "f5cb26", "ff9966", "db0000"
        };
        return colors[palette];
    }

    std::string get_colored_str(const char *content, palette_t palette) {
        return std::string("#") + get_palette_hex(palette) + " " + content + "#";
    }

    void bar_set_default_style(lv_obj_t *bar) {
        lv_obj_remove_style_all(bar);  /*To have a clean start*/
        static lv_style_t style_bg;
        lv_style_init(&style_bg);
        lv_style_set_border_color(&style_bg, get_palette_rgb(palette_success));
        lv_style_set_border_width(&style_bg, 2);
        lv_style_set_pad_all(&style_bg, 6); /*To make the indicator smaller*/
        lv_style_set_radius(&style_bg, 6);
        lv_style_set_anim_time(&style_bg, 1000);

        static lv_style_t style_indic;
        lv_style_init(&style_indic);
        lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
        lv_style_set_bg_color(&style_indic, get_palette_rgb(palette_success));
        lv_style_set_radius(&style_indic, 3);

        lv_obj_add_style(bar, &style_bg, 0);
        lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    }

    void label_set_style(lv_obj_t *label, const lv_font_t *font, lv_color_t color, lv_text_align_t align) {
        lv_obj_set_style_text_font(label, font, 0);
        lv_obj_set_style_text_color(label, color, 0);
        lv_obj_set_style_text_align(label, align, 0);
    }
}
//endregion
