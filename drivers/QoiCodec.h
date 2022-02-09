//
// Created by sungaoran on 2022/1/16.
//

#ifndef UI_SANDBOX_QOICODEC_H
#define UI_SANDBOX_QOICODEC_H

#include "filesystem"
#include "vector"
#include "functional"
#include "mutex"
#include "iostream"
#include "fstream"

#define QOI_OP_INDEX        0x00 /* 00xxxxxx */
#define QOI_OP_DIFF         0x40 /* 01xxxxxx */
#define QOI_OP_LUMA         0x80 /* 10xxxxxx */
#define QOI_OP_RUN          0xc0 /* 11xxxxxx */
#define QOI_OP_RGB          0xfe /* 11111110 */
#define QOI_OP_RGBA         0xff /* 11111111 */

#define QOI_MASK_2          0xc0 /* 11000000 */

#define QOI_COLOR_HASH(C)   (C.rgba.r*3 + C.rgba.g*5 + C.rgba.b*7 + C.rgba.a*11)
#define QOI_HEADER_SIZE     14
#define QOI_BUF_MAX_N       320*8

typedef std::function<void(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data)> qoi_decode_cb_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned char channels;
    unsigned char colorspace;
} qoi_desc;

typedef union {
    struct {
        unsigned char r, g, b, a;
    } rgba;
    unsigned int v;
} qoi_rgba_t;

class QoiCodec {
public:
    //region Singleton
    /* todo use it or not use it, this is a question */
    static QoiCodec &instance() {
        static std::shared_ptr<QoiCodec> instance(new QoiCodec());
        return *instance.get();
    }

    QoiCodec(const QoiCodec &) = delete;

    QoiCodec(QoiCodec &&) = delete;

    QoiCodec &operator=(const QoiCodec &) = delete;

    QoiCodec &operator=(QoiCodec &&) = delete;
    //endregion

    QoiCodec();

    void decode_img(const char *filepath, const qoi_decode_cb_t &cb = nullptr);

    void decode_video(const char *filepath, const qoi_decode_cb_t &cb = nullptr);

    void decode_video_routine();

    qoi_desc &get_current_desc(){
        return m_current_desc;
    }

private:
    void read_header();

    static unsigned int qoi_read_32(const unsigned char *bytes, int *p);

    static void qoi_write_32(unsigned char *bytes, int *p, unsigned int v);


    bool open_file(const char *filepath);

    void decode(unsigned len);

    static uint16_t to_rgb565(qoi_rgba_t rgb);

    std::mutex qoi_mutex;
    qoi_desc m_current_desc;
    std::ifstream m_file;
    int m_cb_buf_h = 0;
    unsigned int m_cb_buf_size = 0;
    unsigned m_frame_size = 0;
    qoi_decode_cb_t m_decode_cb = nullptr;
    uint8_t *m_file_buf;
    const unsigned char qoi_padding[8] = {0, 0, 0, 0, 0, 0, 0, 1};
};


#endif //UI_SANDBOX_QOICODEC_H
