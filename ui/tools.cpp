//
// Created by sungaoran on 2022/1/18.
//

#include "tools.h"
#include "drivers/QoiCodec.h"
#include "drivers/common.h"

static void decode_to_canvas_cb(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data) {
    /* assume x===0 */
    int ptr = w * y;
    memcpy(get_canvas_buf() + ptr, data, w * h * sizeof(uint16_t));
}

std::string current_asset;

void anim_canvas_reset_asset(){
    current_asset = "";
}

void anim_canvas_bind_asset(lv_obj_t *canvas, std::string asset_name, bool reset){
    if (reset || current_asset!=asset_name){
        current_asset = asset_name;
        anim_canvas_bind(canvas, get_asset_path(asset_name).c_str());
    }
}

void anim_canvas_bind(lv_obj_t *canvas, const char *filepath) {
    QoiCodec &qoi = QoiCodec::instance();
    qoi.decode_video(filepath, &decode_to_canvas_cb);
    uint16_t w = qoi.get_current_desc().width;
    uint16_t h = qoi.get_current_desc().height;
    lv_canvas_set_buffer(canvas, get_canvas_buf(), w, h, LV_IMG_CF_TRUE_COLOR);
}

void anim_canvas_update(lv_obj_t *canvas) {
    QoiCodec::instance().decode_video_routine();
    lv_obj_invalidate(canvas);
}

std::string get_asset_path(std::string &asset_name) {
    return std::string(PATH_ASSETS) + asset_name + ".mqoi";
}

lv_anim_t anim_create(lv_obj_t *obj, lv_anim_exec_xcb_t exec_cb, int value_start, int value_end, uint32_t time, uint32_t delay, uint32_t playback_time, uint32_t playback_delay,
                      lv_anim_ready_cb_t ready_cb, void *user_data, lv_anim_path_cb_t path) {
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_exec_cb(&a,exec_cb);
    lv_anim_set_values(&a,value_start,value_end);
    lv_anim_set_time(&a,time);
    if (delay){
        lv_anim_set_delay(&a, delay);
    }
    if (playback_time) {
        lv_anim_set_playback_time(&a, playback_time);
        lv_anim_set_playback_delay(&a, playback_delay);
    }
    lv_anim_set_path_cb(&a, path);
    lv_anim_set_ready_cb(&a,ready_cb);
    lv_anim_set_user_data(&a,user_data);
    return a;
}

void anim_fade(void *var, int32_t value) {
    lv_obj_set_style_opa((lv_obj_t*)var,value,0);
}

void anim_move_ver(void *var, int32_t value) {
    lv_obj_set_y((lv_obj_t*)var,value);
}

void anim_move_hor(void *var, int32_t value) {
    lv_obj_set_x((lv_obj_t*)var,value);
}
