//
// Created by sungaoran on 2022/1/16.
//

#include "QoiCodec.h"
#include "utils/log.h"
#include "common.h"
#include "ui/tools.h"

QoiCodec::QoiCodec() {
//    m_file_buf = (uint8_t *) heap_caps_malloc(1024 * 40, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    m_file_buf = (uint8_t *) malloc(QOI_FILE_BUF_SIZE);
}

void QoiCodec::read_header() {
    if (!m_file) {
        return;
    }
    unsigned char bytes[QOI_HEADER_SIZE];
    m_file.read((char *) bytes, QOI_HEADER_SIZE);
    int p = 4;  /* skip magic */
    m_current_desc.width = qoi_read_32(bytes, &p);
    m_current_desc.height = qoi_read_32(bytes, &p);
    m_current_desc.channels = bytes[p++];
//    m_current_desc.colorspace = bytes[p++];

    m_cb_buf_h = QOI_BUF_MAX_N / m_current_desc.width;
    m_cb_buf_size = m_cb_buf_h * m_current_desc.width;
    m_frame_size = m_current_desc.width * m_current_desc.height;
}


void QoiCodec::decode_img(const char *filepath, const qoi_decode_cb_t &cb) {
    if (open_file(filepath)) {
        std::filesystem::path path = filepath;
        unsigned size = std::filesystem::file_size(path);
        /* todo smaller ram footprint */
        m_file.read((char *) m_file_buf, size - QOI_HEADER_SIZE);
        decode();
        if (cb) {
            m_decode_cb = cb;
        }
        /*else {
            int x_offset = (320 - (int) m_current_desc.width) / 2;
            int y_offset = (240 - (int) m_current_desc.height) / 2;
            m_decode_cb = [x_offset, y_offset](uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data) {
                IvyAnim::instance().Tft.pushImageDMA(x + x_offset, y + y_offset, w, h, data);
            };
        }*/
    }
}

bool QoiCodec::open_file(const char *filepath) {
    if (m_file.is_open()) {
        m_file.close();
    }
    m_file.open(filepath, std::ios::binary);
    if (!m_file) {
        log_w("non-exist file %s", filepath);
        m_file.open("/assets/notfound.mqoi", std::ios::binary);
    }
    read_header();
    return m_file.is_open();
}

bool QoiCodec::decode_video(const char *filepath, const qoi_decode_cb_t &cb) {
    if (open_file(filepath)) {
        if (cb) {
            m_decode_cb = cb;
        }
//        else {
//            int x_offset = (320 - (int) m_current_desc.width) / 2;
//            int y_offset = (240 - (int) m_current_desc.height) / 2;
//            m_decode_cb = [x_offset, y_offset](uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data) {
//                IvyAnim::instance().Tft.pushImageDMA(x + x_offset, y + y_offset, w, h, data);
//            };
//        }
        return true;
    }
    return false;
}

bool QoiCodec::decode_video_routine() {
//    if (!m_file) {
//        return;
//    }
//    m_file.seek(m_offset);
    if (m_file.peek() == EOF) {
        m_file.seekg(QOI_HEADER_SIZE);   /* go to start */
    }
    unsigned char buf[4];
    int p = 0;
    m_file.read((char *) buf, 4);
    m_frame_len = qoi_read_32(buf, &p);
    log_d("len:%d",m_frame_len);
//    m_file.read((char *) m_file_buf, content_size);
    decode();
    return true;
}


bool QoiCodec::read_to_buf() {
    if (m_frame_len<current_offset){
        log_e("invalid buf offset");
        return false;
    }
    unsigned read_len = QOI_FILE_BUF_SIZE;
    if (m_frame_len < current_offset + QOI_FILE_BUF_SIZE) {
        read_len = m_frame_len - current_offset;
    }
    m_file.read((char *) m_file_buf, read_len);
//    log_d("xxxx %d",current_offset);
    last_offset = current_offset;
    current_offset +=read_len;
    return true;
}

uint8_t QoiCodec::get_next_pix(unsigned int index) {
    if (index>=current_offset){
        if (!read_to_buf()){
            return 0;
        }
    }
    return m_file_buf[index-last_offset];
}


void QoiCodec::decode() {
    /*
     * 1. read current frame into file buf
     * 2. decode content in ram
     * 3. send data to scr via dma
     * */

    /* decode data */
    int run = 0;
//    unsigned px_len = m_current_desc.width * m_current_desc.height;
    unsigned chunks_len, px_pos;
    qoi_rgba_t index[64];
    qoi_rgba_t px;

    px.rgba.r = 0;
    px.rgba.g = 0;
    px.rgba.b = 0;
    px.rgba.a = 255;

    chunks_len = m_frame_len - (int) sizeof(qoi_padding);

    int round = 0;
    unsigned buf_p = 0;
    int p = 0;
    bool buf_i = false;
    uint16_t **bufs = get_dma_bufs();
    current_offset = 0;

    for (px_pos = 0; px_pos < m_frame_size; px_pos++) {
        if (run > 0) {
            run--;
        } else if (p < chunks_len) {
//            int b1 = m_file_buf[p++];
            int b1 = get_next_pix(p++);

            if (b1 == QOI_OP_RGB) {
                px.rgba.r = get_next_pix(p++);
                px.rgba.g = get_next_pix(p++);
                px.rgba.b = get_next_pix(p++);
            } else if (b1 == QOI_OP_RGBA) {
                px.rgba.r = get_next_pix(p++);
                px.rgba.g = get_next_pix(p++);
                px.rgba.b = get_next_pix(p++);
                px.rgba.a = get_next_pix(p++);
            } else if ((b1 & QOI_MASK_2) == QOI_OP_INDEX) {
                px = index[b1];
            } else if ((b1 & QOI_MASK_2) == QOI_OP_DIFF) {
                px.rgba.r += ((b1 >> 4) & 0x03) - 2;
                px.rgba.g += ((b1 >> 2) & 0x03) - 2;
                px.rgba.b += (b1 & 0x03) - 2;
            } else if ((b1 & QOI_MASK_2) == QOI_OP_LUMA) {
                int b2 = get_next_pix(p++);
                int vg = (b1 & 0x3f) - 32;
                px.rgba.r += vg - 8 + ((b2 >> 4) & 0x0f);
                px.rgba.g += vg;
                px.rgba.b += vg - 8 + (b2 & 0x0f);
            } else if ((b1 & QOI_MASK_2) == QOI_OP_RUN) {
                run = (b1 & 0x3f);
            }

            index[QOI_COLOR_HASH(px) % 64] = px;    /* todo further reduce calculation */
        }
        bufs[buf_i][buf_p] = to_rgb565(px);
        buf_p++;

        if (buf_p == m_cb_buf_size) {
            m_decode_cb(0, round * m_cb_buf_h, (int) m_current_desc.width, m_cb_buf_h, bufs[buf_i]);

            buf_i = !buf_i;
            buf_p = 0;
            round++;
        }
    }
    if (buf_p) {
        int h = (int) (buf_p / m_current_desc.width);

        m_decode_cb(0, round * m_cb_buf_h, (int) m_current_desc.width, h, bufs[buf_i]);
//        if (!m_decode_cb) {
//            IvyAnim::instance().Tft.pushImageDMA(0, round * m_cb_buf_h, (int) m_current_desc.width, h, bufs[buf_i]);
//        } else {
//            m_decode_cb(0, round * m_cb_buf_h, (int) m_current_desc.width, h, bufs[buf_i]);
//        }
    }

}

uint16_t QoiCodec::to_rgb565(qoi_rgba_t rgb) {
    auto r = (uint16_t) rgb.rgba.r >> 3;
    auto g = (uint16_t) rgb.rgba.g >> 2;
    auto b = (uint16_t) rgb.rgba.b >> 3;
    uint16_t ret = (r << 11) | (g << 5) | (b << 0);
    return __builtin_bswap16(ret);
}

unsigned int QoiCodec::qoi_read_32(const unsigned char *bytes, int *p) {
    unsigned int a = bytes[(*p)++];
    unsigned int b = bytes[(*p)++];
    unsigned int c = bytes[(*p)++];
    unsigned int d = bytes[(*p)++];
    return a << 24 | b << 16 | c << 8 | d;
}

void QoiCodec::qoi_write_32(unsigned char *bytes, int *p, unsigned int v) {
    bytes[(*p)++] = (0xff000000 & v) >> 24;
    bytes[(*p)++] = (0x00ff0000 & v) >> 16;
    bytes[(*p)++] = (0x0000ff00 & v) >> 8;
    bytes[(*p)++] = (0x000000ff & v);
}
