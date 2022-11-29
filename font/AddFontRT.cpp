//
// Created by Huwensong on 2022/5/16.
//
/***
 * 解析lv_font_conv生成的二进制字库文件
 * 参考链接：https://github.com/lvgl/lv_font_conv/blob/master/doc/font_spec.md
 */

#include <cstdint>
#include <cmath>
#include <string>



#include "AddFontRT.h"
#if PC_FILE_RW
    #include <iostream>
    #include <fstream>
    #include <assert.h>

    #include <stdio.h>
#else
#include "FS.h"
#include "SD_MMC.h"

#include "esp_heap_caps.h"
#endif


const uint32_t MAX_MEM = 1024 * 1024 * 6;  // 6MB


/***
 *
 * PUBLIC FUN
 */
CNFont::CNFont()
{

}

CNFont::~CNFont()
{
    lv_font_free();
    free(m_font_dsc);
    free(m_font);
}


bool CNFont::lv_font_load()
{
    bool ret = init();
    if(!ret)
    {
        free(m_init_p);
        return false;
    }
    load_font();
    return true;


}

lv_font_t *CNFont::get_font()
{
    return m_font;
}




/***
 *
 * PRIVATE FUN
 */

//void CNFont::open(String path)
//{
//    uint32_t m_start_pos = 0;
//    uint32_t m_cur_pos = 0;
//    uint32_t m_end_pos = m_start_pos + size;
//}
//void CNFont::seek(uint32_t pos,SeekMode mode)
//{
//    if(pos >= m_start_pos && pos <= m_end_pos)
//    {
//        switch (mode)
//        {
//            case fs::SeekSet:
//                m_cur_pos = m_start_pos + pos;
//                break;
//            case fs::SeekCur:
//                m_cur_pos += pos;
//                m_cur_pos -= pos;
//                break;
//            case fs::SeekEnd:
//                m_cur_pos = m_end_pos - pos;
//                break;
//        }
//    }
//}
//void CNFont::read(void *buf,size_t size)
//{
//    memcpy(buf,m_init_p + m_cur_pos,size);
//    m_cur_pos += size;
//    if (m_cur_pos >= m_end_pos)
//        return 0;
//    if(m_cur_pos < m_start_pos)
//        return -1;
//    return size;
//
//}
bool CNFont::init()
{
    bool ret = init_font();
    if(!ret)
        return false;
    init_psram();
    return true;
}

bool CNFont::init_font()
{
#if PC_FILE_RW == 0
    uint32_t file_size;
    uint32_t read_size;
    File file = SD_MMC.open(m_path, FILE_READ);
    if (!file)
        return false;
    file_size = file.size();
    if (file_size <= 0 || file_size > MAX_MEM)
        return false;

    m_init_p = (uint8_t *) psram_malloc(file_size);

    read_size = file.read(m_init_p, file_size);
    if(read_size <= 0 || read_size != file_size)
        return false;
    file.close();
    return true;
#else
    //std::string path ="E:\\HWS\\font\\fz\\fz_4_16.bin";
    //std::string path ="E:\\HWS\\font\\fz\\fz_4_30.bin";
    std::string path ="E:\\HWS\\font\\fz\\fz_4_40.bin";
    std::ifstream file;
    file.open(path.c_str(),std::ios::binary | std::ios::in);
    assert(file);
    if(file.is_open())
    {
        file.seekg(0, std::ios::end);
       std::streampos file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        if (file_size <= 0 || file_size > MAX_MEM)
            return false;
        m_init_p = (uint8_t *) psram_malloc(file_size);
        file.read((char *)m_init_p,file_size);
        file.close();
        return true;
    }
    else
        return false;
//    FILE *in_file;
//    in_file = fopen("E:\\HWS\\font\\fz\\fz_4_16.bin","rb");
//    if(in_file)
//    {
//        fseek(in_file,0L,SEEK_END);
//        uint32_t file_size = ftell(in_file);
//        fseek(in_file,0L,SEEK_SET);
//        if (file_size <= 0 || file_size > MAX_MEM)
//            return false;
//
//        m_init_p = (uint8_t *) psram_malloc(file_size);
//        fread(m_init_p, sizeof(uint8_t),file_size,in_file);
//        fclose(in_file);
//        return true;
//    }
//    else
//        return false;
#endif
}

void CNFont::init_psram()
{

    m_font = (lv_font_t *)psram_malloc(sizeof(lv_font_t));
    m_font_dsc = (lv_font_fmt_txt_dsc_t *)psram_malloc(sizeof(lv_font_fmt_txt_dsc_t));

    memset(m_font_dsc,0,sizeof(lv_font_fmt_txt_dsc_t));
    memset(m_font,0,sizeof(lv_font_t));

    m_temp_size = m_temp_size + sizeof(lv_font_t) + sizeof(lv_font_fmt_txt_dsc_t);
}

bool CNFont::load_font()
{
    /*load header*/
    uint32_t head_start = 0;
    uint32_t head_length = 0;

    uint32_t font_header_offset = 8;  // font_header_bin_t 数据偏移为 8.
    font_header_bin_t font_header;

    head_length = read_label(head_start,"head");
    if(head_length < 0)
    {
        return false;
    }

    memcpy(&font_header,m_init_p + font_header_offset, sizeof(font_header_bin_t));

    m_font->dsc = m_font_dsc;
    m_font->base_line = -font_header.descent;
    m_font->line_height = font_header.ascent - font_header.descent;
    m_font->get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt;
    m_font->get_glyph_bitmap = lv_font_get_bitmap_fmt_txt;
    m_font->subpx = font_header.subpixels_mode;
    m_font->underline_position = font_header.underline_position;
    m_font->underline_thickness = font_header.underline_thickness;

    m_font_dsc->bpp = font_header.bits_per_pixel;
    m_font_dsc->kern_scale = font_header.kerning_scale;
    m_font_dsc->bitmap_format = font_header.compression_id;

    /*load cmaps*/
    uint32_t cmap_start = head_length;
    uint32_t cmap_length = load_cmaps(cmap_start);
    if(cmap_length < 0)
    {
        return false;
    }

    /*load loca*/
    uint32_t loca_start = cmap_start + cmap_length;
    uint32_t loca_length = read_label( loca_start, "loca");
    if (loca_length < 0)
    {
        return false;
    }

    uint32_t loca_count = 0;
    uint32_t loca_count_offset = 8;
    memcpy(&loca_count,m_init_p + loca_start + loca_count_offset, sizeof(uint32_t));

    bool failed = false;
    uint32_t *glyph_offset = (uint32_t *) psram_malloc(sizeof(uint32_t) * (loca_count + 1));
    LV_LOG_INFO("in proces loca memory = %d Byte",sizeof(uint32_t) * (loca_count + 1));

    uint32_t date_offset =  loca_start + loca_count_offset + sizeof(uint32_t);
    //LV_LOG_INFO("loca_count = %d",loca_count);
    if (font_header.index_to_loc_format == 0)
    {
        for (unsigned int i = 0; i < loca_count; ++i)
        {
            uint16_t offset;
            memcpy(&offset, m_init_p + (date_offset + i * sizeof(uint16_t)), sizeof(uint16_t));
            //LV_LOG_INFO("offset = %d",offset);
            glyph_offset[i] = offset;
            failed = false;
        }
    } else if (font_header.index_to_loc_format == 1)
    {
        memcpy(glyph_offset,m_init_p + date_offset , loca_count * sizeof(uint32_t));
        failed = false;
    } else
    {
        LV_LOG_WARN("Unknown index_to_loc_format: %d.", font_header.index_to_loc_format);
        failed = true;
    }

    if (failed)
    {
        psram_free(glyph_offset);
        return false;
    }



    /*load glyph*/
    uint32_t glyph_start = loca_start + loca_length;
    int32_t glyph_length = load_glyph(glyph_start, glyph_offset, loca_count,font_header);
    psram_free(glyph_offset);

    if (glyph_length < 0)
    {
        return false;
    }

    //LV_LOG_INFO("font_header.tables_count = %d",font_header.tables_count);
    if (font_header.tables_count < 4)
    {
        m_font_dsc->kern_dsc = nullptr;
        m_font_dsc->kern_classes = 0;
        m_font_dsc->kern_scale = 0;
        LV_LOG_INFO("memory alloc is %d KB",m_temp_size / 1024);
        return true;
    }

    /*load kern*/
    uint32_t kern_start = glyph_start + glyph_length;

    int32_t kern_length = load_kern(kern_start,  font_header.glyph_id_format);
    LV_LOG_INFO("memory alloc is %d KB",m_temp_size / 1024);


    return kern_length >= 0;




}

void CNFont::lv_font_free()
{
    lv_font_fmt_txt_dsc_t *dsc = (lv_font_fmt_txt_dsc_t *) m_font->dsc;

    if (nullptr != dsc)
    {

        if (dsc->kern_classes == 0)
        {
            lv_font_fmt_txt_kern_pair_t *kern_dsc =
                    (lv_font_fmt_txt_kern_pair_t *) dsc->kern_dsc;

            if (nullptr != kern_dsc)
            {
                if (kern_dsc->glyph_ids)
                    psram_free((void *) kern_dsc->glyph_ids);

                if (kern_dsc->values)
                    psram_free((void *) kern_dsc->values);

                psram_free((void *) kern_dsc);
            }
        }
        else
        {
            lv_font_fmt_txt_kern_classes_t *kern_dsc =
                    (lv_font_fmt_txt_kern_classes_t *) dsc->kern_dsc;

            if (nullptr != kern_dsc)
            {
                if (kern_dsc->class_pair_values)
                    psram_free((void *) kern_dsc->class_pair_values);

                if (kern_dsc->left_class_mapping)
                    psram_free((void *) kern_dsc->left_class_mapping);

                if (kern_dsc->right_class_mapping)
                    psram_free((void *) kern_dsc->right_class_mapping);

                psram_free((void *) kern_dsc);
            }
        }

        lv_font_fmt_txt_cmap_t *cmaps =
                (lv_font_fmt_txt_cmap_t *) dsc->cmaps;

        if (nullptr != cmaps)
        {
            for (int i = 0; i < dsc->cmap_num; ++i)
            {
                if (nullptr != cmaps[i].glyph_id_ofs_list)
                    psram_free((void *) cmaps[i].glyph_id_ofs_list);
                if (nullptr != cmaps[i].unicode_list)
                    psram_free((void *) cmaps[i].unicode_list);
            }
            psram_free(cmaps);
        }

        if (nullptr != dsc->glyph_bitmap)
        {
            psram_free((void *) dsc->glyph_bitmap);
        }
        if (nullptr != dsc->glyph_dsc)
        {
            psram_free((void *) dsc->glyph_dsc);
        }
        psram_free(dsc);
    }
}

uint32_t CNFont::read_label(uint32_t start,const char *label)
{
    uint32_t length = 0;
    char buff[4] = {"0"};
    memcpy(&length, m_init_p + start, sizeof(uint32_t));
    memcpy(buff, m_init_p + start + 4, 4);

    if(length <= 0 || memcmp(buff,label,4) != 0)
    {
        return -1;
    }
    return length;

};

uint32_t CNFont::read_bits(uint32_t start, bit_iterator_t &it, int n_bits)
{
    unsigned int value = 0;

    while (n_bits--)
    {
        it.byte_value = it.byte_value << 1;
        it.bit_pos--;


        if (it.bit_pos < 0)
        {

            it.bit_pos = 7;
            memcpy(&it.byte_value,m_init_p + start + m_read_bit_count,1);
            m_read_bit_count ++;

        }

        int8_t bit = (it.byte_value & 0x80) ? 1 : 0;

        value |= (bit << n_bits);
    }
    return value;
}

int CNFont::read_bits_signed(uint32_t start, bit_iterator_t &it, int n_bits)
{
    unsigned value = read_bits(start, it, n_bits);
    //LV_LOG_INFO("SIGNED READ BITS  byte_value = %d",value);
    if (value & (1 << (n_bits - 1)))
    {
        value |= ~0u << n_bits;
    }
    return (int)value;
}

bool CNFont::load_cmaps_table(uint32_t start,cmap_table_bin_t *cmap_table)
{
    memcpy(cmap_table,m_init_p + start,m_font_dsc->cmap_num * sizeof(cmap_table_bin_t));

    uint32_t offset = 0;
    for (unsigned int i = 0; i < m_font_dsc->cmap_num; ++i)
    {
        lv_font_fmt_txt_cmap_t *cmap = (lv_font_fmt_txt_cmap_t *) &(m_font_dsc->cmaps[i]);

        cmap->range_start = cmap_table[i].range_start;
        cmap->range_length = cmap_table[i].range_length;
        cmap->glyph_id_start = cmap_table[i].glyph_id_start;
        cmap->type = cmap_table[i].format_type;

        offset = (start - 12) + cmap_table[i].data_offset;

        switch (cmap_table[i].format_type)
        {
            case LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL:
            {
                uint8_t ids_size = sizeof(uint8_t) * cmap_table[i].data_entries_count;
                uint8_t *glyph_id_ofs_list = (uint8_t *) psram_malloc(ids_size);

                m_temp_size += ids_size;
                cmap->glyph_id_ofs_list = glyph_id_ofs_list;

                memcpy(glyph_id_ofs_list,m_init_p + offset,ids_size);

                cmap->list_length = cmap->range_length;
                break;
            }
            case LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY:
                break;
            case LV_FONT_FMT_TXT_CMAP_SPARSE_FULL:
            case LV_FONT_FMT_TXT_CMAP_SPARSE_TINY:
            {
                uint32_t list_size = sizeof(uint16_t) * cmap_table[i].data_entries_count;
                uint16_t *unicode_list = (uint16_t *) psram_malloc(list_size);

                cmap->unicode_list = unicode_list;
                cmap->list_length = cmap_table[i].data_entries_count;
                m_temp_size += list_size;
                memcpy(unicode_list,m_init_p + offset,list_size);

                if (cmap_table[i].format_type == LV_FONT_FMT_TXT_CMAP_SPARSE_FULL)
                {
                    uint16_t *buf = (uint16_t *) psram_malloc(sizeof(uint16_t) * cmap->list_length);
                    m_temp_size += sizeof(uint16_t) * cmap->list_length;

                    cmap->glyph_id_ofs_list = buf;
                    memcpy(buf,m_init_p + offset + list_size,sizeof(uint16_t) * cmap->list_length);
                }
                break;
            }
            default:
                LV_LOG_WARN("Unknown cmaps format type %d.", cmap_table[i].format_type);
                return false;
        }
    }
    return true;
}

uint32_t CNFont::load_cmaps(uint32_t start)
{
    uint32_t cmaps_subtables_count = 0;
    uint32_t subtables_count_offset = 8;  // subtables_count 数据地址偏移为 8.

    uint32_t cmaps_length = read_label(start,"cmap");
    //LV_LOG_INFO("load_cmaps cmaps_length = %d",cmaps_length);
    if(cmaps_length < 0)
    {
        return -1;
    }

    memcpy(&cmaps_subtables_count,m_init_p + start + subtables_count_offset, sizeof(uint32_t));
    //LV_LOG_INFO("cmaps_subtables_count = %d",cmaps_subtables_count);
    m_cmaps = (lv_font_fmt_txt_cmap_t *) psram_malloc(cmaps_subtables_count * sizeof(lv_font_fmt_txt_cmap_t));
    memset(m_cmaps,0,cmaps_subtables_count * sizeof(lv_font_fmt_txt_cmap_t));
    m_font_dsc->cmaps = m_cmaps;
    m_font_dsc->cmap_num = cmaps_subtables_count;

    cmap_table_bin_t *cmaps_tables = (cmap_table_bin_t *) psram_malloc(
            sizeof(cmap_table_bin_t) * m_font_dsc->cmap_num);
    LV_LOG_INFO("in proces cmap memory = %d Byte",sizeof(cmap_table_bin_t) * m_font_dsc->cmap_num);


    //load cmaps table
    uint32_t cmaps_table_start = start + subtables_count_offset + sizeof(uint32_t);
    bool success = load_cmaps_table(cmaps_table_start, cmaps_tables);

    psram_free(cmaps_tables);

    return success ? cmaps_length : -1;
}

int32_t CNFont::load_glyph(uint32_t start,const uint32_t *glyph_offset,uint32_t loca_count,font_header_bin_t &header)
{
    uint32_t glyph_length = read_label(start, "glyf");
    if (glyph_length < 0)
    {
        return -1;
    }

    lv_font_fmt_txt_glyph_dsc_t *glyph_dsc = (lv_font_fmt_txt_glyph_dsc_t *)
            psram_malloc(loca_count * sizeof(lv_font_fmt_txt_glyph_dsc_t));
    m_temp_size += loca_count * sizeof(lv_font_fmt_txt_glyph_dsc_t);
    memset(glyph_dsc, 0, loca_count * sizeof(lv_font_fmt_txt_glyph_dsc_t));

    m_font_dsc->glyph_dsc = glyph_dsc;

    int cur_bmp_size = 0;


    for (unsigned int i = 0; i < loca_count; ++i)
    {
        lv_font_fmt_txt_glyph_dsc_t *gdsc = &glyph_dsc[i];

        uint32_t start_offset = start + glyph_offset[i];
        m_read_bit_count = 0;

        bit_iterator_t bit_it = bit_iterator_t(-1, 0);

        if (header.advance_width_bits == 0)
        {
            gdsc->adv_w = header.default_advance_width;
        }
        else
        {
            gdsc->adv_w = read_bits(start_offset, bit_it, header.advance_width_bits);
        }

        if (header.advance_width_format == 0)
        {
            gdsc->adv_w *= 16;
        }


        gdsc->ofs_x = read_bits_signed(start_offset, bit_it, header.xy_bits);

        gdsc->ofs_y = read_bits_signed(start_offset , bit_it, header.xy_bits);

        gdsc->box_w = read_bits(start_offset, bit_it, header.wh_bits);

        gdsc->box_h = read_bits(start_offset, bit_it, header.wh_bits);

        int nbits = header.advance_width_bits + 2 * header.xy_bits + 2 * header.wh_bits;
        int next_offset = (i < loca_count - 1) ? glyph_offset[i + 1] :  glyph_length;
        int bmp_size = next_offset - glyph_offset[i] - nbits / 8;

        if (i == 0)
        {
            gdsc->adv_w = 0;
            gdsc->box_w = 0;
            gdsc->box_h = 0;
            gdsc->ofs_x = 0;
            gdsc->ofs_y = 0;
        }

        gdsc->bitmap_index = cur_bmp_size;
        if (gdsc->box_w * gdsc->box_h != 0)
        {
            cur_bmp_size += bmp_size;
        }


    }

    uint8_t *glyph_bmp = (uint8_t *) psram_malloc(sizeof(uint8_t) * cur_bmp_size);
    m_temp_size += sizeof(uint8_t) * cur_bmp_size;

    m_font_dsc->glyph_bitmap = glyph_bmp;
//    std::copy(vec_glyph_bmp.begin(),vec_glyph_bmp.end(),glyph_bmp);
//    LV_LOG_WARN("b vec mem = %d", vec_glyph_bmp.size());
//    vec_glyph_bmp.clear();
//    std::vector<uint8_t> ().swap(vec_glyph_bmp);
//    LV_LOG_WARN("vec mem = %d", vec_glyph_bmp.size());


    cur_bmp_size = 0;


    for (unsigned int i = 1; i < loca_count; ++i)
    {
        uint32_t start_offset = start + glyph_offset[i];
        m_read_bit_count = 0;


        bit_iterator_t bit_it = bit_iterator_t(-1, 0);

        int nbits = header.advance_width_bits + 2 * header.xy_bits + 2 * header.wh_bits;

        read_bits(start_offset, bit_it, nbits);

        if (glyph_dsc[i].box_w * glyph_dsc[i].box_h == 0)
        {
            continue;
        }

        int next_offset = (i < loca_count - 1) ? glyph_offset[i + 1] : (uint32_t) glyph_length;
        int bmp_size = next_offset - glyph_offset[i] - nbits / 8;

        if (nbits % 8 == 0)
        {
            memcpy(&glyph_bmp[cur_bmp_size],m_init_p + start_offset + m_read_bit_count,bmp_size);
        }
        else
        {
            for (int k = 0; k < bmp_size - 1; ++k)
            {
                glyph_bmp[cur_bmp_size + k] = read_bits(start_offset, bit_it, 8);
            }
            glyph_bmp[cur_bmp_size + bmp_size - 1] = read_bits(start_offset, bit_it, 8 - nbits % 8);

            /*The last fragment should be on the MSB but read_bits() will place it to the LSB*/
            glyph_bmp[cur_bmp_size + bmp_size - 1] = glyph_bmp[cur_bmp_size + bmp_size - 1] << (nbits % 8);

        }

        cur_bmp_size += bmp_size;
    }
    return glyph_length;
}

int32_t CNFont::load_kern(uint32_t start, uint8_t format)
{
    int32_t kern_length = read_label(start, "kern");
    if (kern_length < 0)
    {
        return -1;
    }

    uint32_t kern_format_offset = 8;
    uint8_t kern_format_type;

    uint32_t padding_offset = 9;
    int32_t padding;

    memcpy(&kern_format_type,m_init_p + start + kern_format_offset, sizeof(uint8_t));
    memcpy(&padding,m_init_p + start +  kern_format_offset + padding_offset,3 * sizeof(uint8_t));

    if (0 == kern_format_type)
    { /*sorted pairs*/
        lv_font_fmt_txt_kern_pair_t *kern_pair = (lv_font_fmt_txt_kern_pair_t *) psram_malloc(
                sizeof(lv_font_fmt_txt_kern_pair_t));
        m_temp_size += sizeof(lv_font_fmt_txt_kern_pair_t);

        memset(kern_pair, 0, sizeof(lv_font_fmt_txt_kern_pair_t));

        m_font_dsc->kern_dsc = kern_pair;
        m_font_dsc->kern_classes = 0;

        uint32_t entries_offset = 12;
        uint32_t glyph_entries;

        memcpy(&glyph_entries,m_init_p + start + entries_offset, sizeof(uint32_t));

        int ids_size;
        if (format == 0)
        {
            ids_size = sizeof(int8_t) * 2 * glyph_entries;
        } else
        {
            ids_size = sizeof(int16_t) * 2 * glyph_entries;
        }


        uint8_t *glyph_ids = (uint8_t *) psram_malloc(ids_size);
        int8_t *values = (int8_t *) psram_malloc(glyph_entries);

        kern_pair->glyph_ids_size = format;
        kern_pair->pair_cnt = glyph_entries;
        kern_pair->glyph_ids = glyph_ids;
        kern_pair->values = values;

        uint32_t ids_offset = 16;
        uint32_t values_offset = ids_offset + ids_size;

        memcpy(glyph_ids,m_init_p + start + ids_offset,ids_size);
        memcpy(values,m_init_p + start + values_offset,glyph_entries);
    }
    else if (3 == kern_format_type)
    { /*array M*N of classes*/

        lv_font_fmt_txt_kern_classes_t *kern_classes =
                (lv_font_fmt_txt_kern_classes_t *) psram_malloc(sizeof(lv_font_fmt_txt_kern_classes_t));

        m_temp_size += sizeof(lv_font_fmt_txt_kern_classes_t);
        memset(kern_classes, 0, sizeof(lv_font_fmt_txt_kern_classes_t));

        m_font_dsc->kern_dsc = kern_classes;
        m_font_dsc->kern_classes = 1;

        uint32_t mapping_length_offset = 12;
        uint16_t kern_class_mapping_length;
        uint8_t kern_table_rows;
        uint8_t kern_table_cols;

        memcpy(&kern_class_mapping_length,(m_init_p + start + mapping_length_offset), sizeof(uint16_t));
        memcpy(&kern_table_rows,(m_init_p + start + mapping_length_offset + sizeof(uint16_t)), sizeof(uint8_t));
        memcpy(&kern_table_cols,(m_init_p + start + mapping_length_offset +  sizeof(uint16_t) + sizeof(uint8_t)),sizeof(uint8_t));


        int kern_values_length = sizeof(int8_t) * kern_table_rows * kern_table_cols;

        uint8_t *kern_left = (uint8_t *) psram_malloc(kern_class_mapping_length);
        uint8_t *kern_right = (uint8_t *) psram_malloc(kern_class_mapping_length);
        int8_t *kern_values = (int8_t *) psram_malloc(kern_values_length);

        kern_classes->left_class_mapping = kern_left;
        kern_classes->right_class_mapping = kern_right;
        kern_classes->left_class_cnt = kern_table_rows;
        kern_classes->right_class_cnt = kern_table_cols;
        kern_classes->class_pair_values = kern_values;


        uint32_t kern_left_offset = 16;
        uint32_t kern_right_offset = kern_left_offset + kern_class_mapping_length;
        uint32_t kern_values_offset = kern_left_offset + 2 * kern_class_mapping_length;

        memcpy(kern_left,m_init_p + start + kern_left_offset,kern_class_mapping_length);
        memcpy(kern_right,m_init_p + start + kern_right_offset,kern_class_mapping_length);
        memcpy(kern_values,m_init_p + start + kern_values_offset,kern_values_length);
    } else
    {
        LV_LOG_WARN("Unknown kern_format_type: %d", kern_format_type);
        return -1;
    }

    return kern_length;
}

void *CNFont::psram_malloc(size_t size)
{
#if PC_FILE_RW == 1
    return malloc(size);
#else
    return heap_caps_malloc(size,MALLOC_CAP_SPIRAM);
#endif
}

void CNFont::psram_free(void *p)
{
    free(p);
}


