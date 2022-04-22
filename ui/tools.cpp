//
// Created by sungaoran on 2022/1/18.
//

#include "tools.h"
#include "drivers/QoiCodec.h"
#include "ui/UIActionBox.h"
#include "drivers/common.h"

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

std::string get_asset_path(std::string &asset_name) {
    return std::string(PATH_ASSETS) + "/" + asset_name + ".mqoi";
}

lv_anim_t
anim_create(lv_obj_t *obj, lv_anim_exec_xcb_t exec_cb, int value_start, int value_end, uint32_t time, uint32_t delay,
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
lv_style_t bar_get_default_style_bg() {
    lv_style_t style;
    lv_style_init(&style);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_border_width(&style, 2);
    lv_style_set_pad_all(&style, 6); /*To make the indicator smaller*/
    lv_style_set_radius(&style, 6);
    lv_style_set_anim_time(&style, 1000);
    return style;
}

lv_style_t bar_get_default_style_indic() {
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_radius(&style, 3);
    return style;
}
//endregion
