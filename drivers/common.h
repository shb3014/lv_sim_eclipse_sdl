//
// Created by sungaoran on 2022/1/19.
//

#ifndef LVGL_COMMON_H
#define LVGL_COMMON_H

#include "cstdint"
#include "chrono"

#define MAX_BUFFERED_PIXELS 5120

uint16_t **get_dma_bufs();

uint16_t *get_canvas_buf();


#endif //LVGL_COMMON_H
