//
// Created by sungaoran on 2022/1/19.
//

#include "common.h"
#include "lv_conf.h"

uint16_t m_buf_a[MAX_BUFFERED_PIXELS];
uint16_t m_buf_b[MAX_BUFFERED_PIXELS];
uint16_t *m_bufs[2] = {m_buf_a, m_buf_b};
uint16_t m_canvas_buf[LV_HOR_RES * LV_VER_RES];

uint16_t **get_dma_bufs() {
    return m_bufs;
}

uint16_t *get_canvas_buf() {
    return m_canvas_buf;
}
