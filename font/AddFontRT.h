//
// Created by Huwensong on 2022/5/16.
//

#ifndef SBOXMEM_ADDFONTRT_H
#define SBOXMEM_ADDFONTRT_H

#define PC_FILE_RW 1

#include <string>

#include "lvgl/lvgl.h"
#if  PC_FILE_RW == 0
#include "src/misc/lv_fs.h"
#endif
#include <memory>

#pragma pack(push,1)

typedef struct BitIteratorTag
{
    int8_t bit_pos;
    uint8_t byte_value;

    BitIteratorTag(int8_t _bit_pos, uint8_t _byte_value) : bit_pos(_bit_pos), byte_value(_byte_value)
    {};
} bit_iterator_t;

typedef struct font_header_bin
{
    uint32_t version;
    uint16_t tables_count;
    uint16_t font_size;
    uint16_t ascent;
    int16_t descent;
    uint16_t typo_ascent;
    int16_t typo_descent;
    uint16_t typo_line_gap;
    int16_t min_y;
    int16_t max_y;
    uint16_t default_advance_width;
    uint16_t kerning_scale;
    uint8_t index_to_loc_format;
    uint8_t glyph_id_format;
    uint8_t advance_width_format;
    uint8_t bits_per_pixel;
    uint8_t xy_bits;
    uint8_t wh_bits;
    uint8_t advance_width_bits;
    uint8_t compression_id;
    uint8_t subpixels_mode;
    uint8_t padding;
    int16_t underline_position;
    uint16_t underline_thickness;
} font_header_bin_t;

typedef struct cmap_table_bin
{
    uint32_t data_offset;
    uint32_t range_start;
    uint16_t range_length;
    uint16_t glyph_id_start;
    uint16_t data_entries_count;
    uint8_t format_type;
    uint8_t padding;
} cmap_table_bin_t;

#pragma pack(pop)

class CNFont
{
public:
    CNFont();
    ~CNFont();


public:
    //单例模式
    static CNFont &instance()
    {
        static std::shared_ptr<CNFont> instance(new CNFont());
        return *instance;
    }


    //从SD卡加载字库文件（二进制）
    bool lv_font_load();

    //获取字体库
    lv_font_t *get_font();



private:
//    void open(String path);
//    void seek(uint32_t pos,SeekMode mode);
//    void read(void *buf,size_t size);

    //初始化内存空间并读取SD卡二进制字库文件到内存
    bool init();
    bool init_font();
    void init_psram();

    //加载字体
    bool load_font();
    //释放内存
    void lv_font_free();

    uint32_t read_label(uint32_t start,const char *label);

    uint32_t read_bits(uint32_t start,bit_iterator_t &it, int n_bits);
    int read_bits_signed(uint32_t start, bit_iterator_t &it, int n_bits);

    bool load_cmaps_table(uint32_t start,cmap_table_bin_t *cmap_table);
    uint32_t load_cmaps(uint32_t start);

    int32_t load_glyph(uint32_t start,const uint32_t *glyph_offset,uint32_t loca_count,font_header_bin_t &header);
    int32_t load_kern(uint32_t start,uint8_t format );

    void *psram_malloc(size_t size);
    void psram_free(void *p);

private:

//    String m_path = "/font/fz_1_16.bin"; // 字库文件路径
//    String m_path = "/font/fz_1_30.bin";
//    String m_path = "/font/fz_4_16.bin";
//
//    String m_path = "/font/fzyd_1_16.bin";
//    String m_path = "/font/fzyd_1_30.bin";
//    String m_path = "/font/fzyd_4_16.bin";

    uint8_t *m_init_p = nullptr;  //初始化内存空间地址


    lv_font_t *m_font = nullptr;

    lv_font_fmt_txt_dsc_t *m_font_dsc = nullptr;

    lv_font_fmt_txt_cmap_t *m_cmaps = nullptr;

    uint32_t m_read_bit_count = 0;


    uint32_t m_temp_size = 0;

};




#endif //SBOXMEM_ADDFONTRT_H
