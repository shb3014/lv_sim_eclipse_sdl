/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#include "lvgl/lvgl.h"

#ifndef MI_DEMI
#define MI_DEMI 1
#endif

#if MI_DEMI

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0xff, 0xf0, 0xf0,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x16, 0x14, 0x14, 0x7f, 0x24, 0x24, 0xfe, 0x28,
    0x28, 0x68,

    /* U+0024 "$" */
    0x31, 0xef, 0xfe, 0xf3, 0xc3, 0xcf, 0x3f, 0xf7,
    0x8c,

    /* U+0025 "%" */
    0x61, 0xa4, 0x49, 0x22, 0x58, 0x64, 0x2, 0x1,
    0x98, 0x49, 0x22, 0x58, 0x60,

    /* U+0026 "&" */
    0x38, 0x6c, 0x6c, 0x7c, 0x38, 0x73, 0xda, 0xce,
    0xce, 0x7b,

    /* U+0027 "'" */
    0x54,

    /* U+0028 "(" */
    0x2d, 0x6d, 0xb6, 0x4c, 0x80,

    /* U+0029 ")" */
    0x99, 0x36, 0xdb, 0x5a, 0x0,

    /* U+002A "*" */
    0x4f, 0xf4,

    /* U+002B "+" */
    0x30, 0xcf, 0xcc, 0x30, 0xc0,

    /* U+002C "," */
    0xf7,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x18, 0x84, 0x63, 0x11, 0x8c, 0x42, 0x0,

    /* U+0030 "0" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6c,
    0x70,

    /* U+0031 "1" */
    0x7f, 0xb3, 0x33, 0x33, 0x33,

    /* U+0032 "2" */
    0x7b, 0x30, 0xc3, 0x1c, 0x63, 0x18, 0x63, 0xf0,

    /* U+0033 "3" */
    0xf8, 0x63, 0x18, 0x78, 0x30, 0xc3, 0xcd, 0xe0,

    /* U+0034 "4" */
    0x1c, 0x38, 0xf1, 0x66, 0xc9, 0xb3, 0x7f, 0xc,
    0x18,

    /* U+0035 "5" */
    0x7c, 0x81, 0x2, 0x7, 0xc8, 0xc1, 0x83, 0xce,
    0xf8,

    /* U+0036 "6" */
    0x18, 0x60, 0xc3, 0xf, 0xdc, 0xf1, 0xe3, 0x6e,
    0x78,

    /* U+0037 "7" */
    0xfc, 0x31, 0x86, 0x18, 0xc3, 0x8, 0x61, 0x80,

    /* U+0038 "8" */
    0x79, 0x9b, 0x36, 0x63, 0x88, 0xb1, 0xe3, 0xc6,
    0xf8,

    /* U+0039 "9" */
    0x39, 0xdb, 0x1e, 0x3c, 0xef, 0xc3, 0xc, 0x18,
    0x60,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0x3d, 0xc0,

    /* U+003C "<" */
    0x0, 0x33, 0xb8, 0xc1, 0xc1, 0xc1,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x3, 0x7, 0x7, 0xc, 0xee, 0x20,

    /* U+003F "?" */
    0x7b, 0x30, 0xc7, 0x38, 0xc3, 0x0, 0x30, 0xc0,

    /* U+0040 "@" */
    0x3e, 0x31, 0x90, 0x73, 0xdb, 0x2d, 0x96, 0x7c,
    0x80, 0x62, 0x1f, 0x0,

    /* U+0041 "A" */
    0x18, 0xe, 0x7, 0x6, 0x83, 0x61, 0x31, 0xf8,
    0xc6, 0x43, 0x60, 0x80,

    /* U+0042 "B" */
    0xfd, 0x8f, 0x1e, 0x3c, 0xff, 0x31, 0xe3, 0xc7,
    0xf8,

    /* U+0043 "C" */
    0x3e, 0x63, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0x60,
    0x63, 0x3e,

    /* U+0044 "D" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2,
    0xc6, 0xfc,

    /* U+0045 "E" */
    0xff, 0xc, 0x30, 0xc3, 0xfc, 0x30, 0xc3, 0xf0,

    /* U+0046 "F" */
    0xff, 0xc, 0x30, 0xc3, 0xfc, 0x30, 0xc3, 0x0,

    /* U+0047 "G" */
    0x3e, 0x67, 0xc2, 0xc0, 0xc0, 0xcf, 0xc3, 0xc3,
    0x67, 0x3e,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xcd, 0xe0,

    /* U+004B "K" */
    0xc6, 0xcc, 0xd8, 0xf8, 0xf0, 0xf8, 0xd8, 0xcc,
    0xc6, 0xc3,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf0,

    /* U+004D "M" */
    0xc0, 0xf8, 0x7e, 0x1f, 0xcf, 0xd2, 0xf7, 0xbc,
    0xcf, 0x3, 0xc0, 0xf0, 0x30,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xdb, 0xdb, 0xcf, 0xc7,
    0xc7, 0xc3,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0xf8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0x63, 0x1f, 0x0,

    /* U+0050 "P" */
    0xfd, 0x9f, 0x1e, 0x3c, 0xff, 0xb0, 0x60, 0xc1,
    0x80,

    /* U+0051 "Q" */
    0x3e, 0x31, 0xb0, 0x58, 0x3c, 0x1e, 0xf, 0x7,
    0x8b, 0x67, 0x1f, 0x80, 0x40,

    /* U+0052 "R" */
    0xfd, 0x9f, 0x1e, 0x3c, 0xff, 0xb2, 0x66, 0xc7,
    0x8c,

    /* U+0053 "S" */
    0x3d, 0x8f, 0x7, 0xf, 0xc7, 0xc3, 0x83, 0xc6,
    0xf8,

    /* U+0054 "T" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6c,
    0x70,

    /* U+0056 "V" */
    0xc1, 0x21, 0x98, 0xcc, 0x42, 0x61, 0xb0, 0xd0,
    0x38, 0x1c, 0xc, 0x0,

    /* U+0057 "W" */
    0xc6, 0x16, 0x38, 0x91, 0xcc, 0xca, 0x66, 0xd2,
    0x36, 0xd0, 0xa7, 0x87, 0x1c, 0x38, 0xc1, 0x86,
    0x0,

    /* U+0058 "X" */
    0x63, 0x66, 0x36, 0x1c, 0x18, 0x1c, 0x3c, 0x36,
    0x63, 0xc3,

    /* U+0059 "Y" */
    0xc3, 0x42, 0x66, 0x24, 0x3c, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+005A "Z" */
    0xfe, 0x1c, 0x30, 0xc1, 0x86, 0xc, 0x30, 0xc1,
    0xfc,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+005C "\\" */
    0xcc, 0x46, 0x62, 0x23, 0x31,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+005E "^" */
    0x31, 0x96, 0x90,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x4c, 0x0,

    /* U+0061 "a" */
    0x79, 0x30, 0xdf, 0xcf, 0x37, 0xc0,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xee, 0xf8, 0xf1, 0xe3, 0xef,
    0xf8,

    /* U+0063 "c" */
    0x39, 0x9c, 0x30, 0xc1, 0x93, 0x80,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xfe, 0xf8, 0xf1, 0xe3, 0x6e,
    0xfc,

    /* U+0065 "e" */
    0x3c, 0xcd, 0x1f, 0xf4, 0xc, 0xcf, 0x0,

    /* U+0066 "f" */
    0x36, 0x6f, 0x66, 0x66, 0x66,

    /* U+0067 "g" */
    0x7f, 0xdf, 0x1e, 0x3c, 0x7d, 0xdf, 0x83, 0xc6,
    0xf8,

    /* U+0068 "h" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+0069 "i" */
    0xf3, 0xff, 0xf0,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0xe0,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x6d, 0x9e, 0x3c, 0x6c, 0xd9,
    0x98,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdc,

    /* U+006D "m" */
    0xfb, 0xb3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcc,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+006F "o" */
    0x38, 0xdb, 0x1e, 0x3c, 0x6d, 0x9e, 0x0,

    /* U+0070 "p" */
    0xfd, 0xdf, 0x1e, 0x3c, 0x7d, 0xff, 0x60, 0xc1,
    0x80,

    /* U+0071 "q" */
    0x7f, 0xdf, 0x1e, 0x3c, 0x7d, 0xdf, 0x83, 0x6,
    0xc,

    /* U+0072 "r" */
    0xfe, 0xcc, 0xcc, 0xc0,

    /* U+0073 "s" */
    0x7b, 0x3e, 0x1e, 0x1f, 0x37, 0x80,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x66, 0x30,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0xc0,

    /* U+0076 "v" */
    0xc6, 0x89, 0xb3, 0x62, 0x87, 0xc, 0x0,

    /* U+0077 "w" */
    0xcc, 0x53, 0x34, 0xed, 0xea, 0x7a, 0x8c, 0xe3,
    0x30,

    /* U+0078 "x" */
    0x44, 0xd8, 0xe0, 0x83, 0x8d, 0xb1, 0x0,

    /* U+0079 "y" */
    0xc6, 0x89, 0xb3, 0x62, 0x87, 0x6, 0x18, 0x30,
    0x40,

    /* U+007A "z" */
    0xfc, 0x71, 0x8c, 0x63, 0x8f, 0xc0,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x70, 0xc6, 0x31, 0x86,

    /* U+007C "|" */
    0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xc6, 0x66, 0x63, 0x66, 0x66, 0xc0,

    /* U+007E "~" */
    0x75, 0xb8,

    /* U+00B0 "°" */
    0x69, 0x96
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 77, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 116, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 167, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 145, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 48, .adv_w = 67, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 67, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 86, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 60, .adv_w = 122, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 65, .adv_w = 55, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 66, .adv_w = 78, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 67, .adv_w = 53, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 84, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 126, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 88, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 107, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 126, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 53, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 55, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 163, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 169, .adv_w = 122, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 172, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 178, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 140, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 145, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 53, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 103, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 139, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 177, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 155, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 155, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 361, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 140, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 204, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 70, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 461, .adv_w = 72, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 70, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 472, .adv_w = 91, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 475, .adv_w = 90, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 476, .adv_w = 58, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 478, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 75, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 529, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 54, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 54, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 547, .adv_w = 111, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 53, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 176, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 591, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 600, .adv_w = 83, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 99, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 78, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 167, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 653, .adv_w = 101, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 73, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 666, .adv_w = 48, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 669, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 675, .adv_w = 112, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 677, .adv_w = 82, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 33, .range_length = 94, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 1, .glyph_id_start = 95,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 2, 0, 2, 3,
    4, 0, 5, 6, 7, 0, 8, 9,
    10, 11, 0, 0, 0, 0, 0, 0,
    0, 12, 13, 14, 15, 16, 17, 18,
    0, 0, 19, 20, 21, 0, 0, 15,
    22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 0, 0, 0, 0, 33,
    0, 34, 35, 36, 0, 37, 38, 39,
    34, 0, 0, 40, 41, 34, 34, 35,
    35, 39, 42, 43, 44, 39, 45, 46,
    47, 45, 48, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 2, 0, 2, 3,
    4, 5, 6, 7, 8, 0, 9, 10,
    11, 12, 0, 0, 0, 0, 0, 0,
    0, 13, 0, 14, 0, 0, 0, 14,
    0, 0, 15, 0, 0, 0, 0, 14,
    0, 14, 0, 16, 17, 18, 19, 20,
    21, 22, 23, 0, 0, 0, 0, 0,
    0, 24, 0, 25, 25, 25, 26, 25,
    0, 0, 27, 0, 28, 29, 29, 25,
    29, 25, 29, 30, 31, 32, 33, 34,
    35, 33, 36, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, -7, 0,
    -15, -4, -13, -8, 0, -19, 0, -5,
    -4, -2, 0, -4, 0, 0, -4, 0,
    -11, -7, 0, 0, 0, 0, 0, 0,
    -13, 0, 0, -7, 0, 0, 0, -11,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -14,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -4, -5,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, -5, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, -7, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -25, -16, -3, 0, 0, 0, -14,
    -12, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -18, -10, 0, 0, 0, 0, -4,
    -2, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, -26, -3, -22, -14,
    0, -22, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, -9, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    -5, 0, -4, -3, -4, -7, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, -1, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -3, 0, 0, 0,
    -6, -2, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -4, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -9, 0,
    -6, 0, -7, -3, -10, -10, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -12, 0, -24, -2,
    0, 0, 0, 0, -4, 0, 0, -11,
    -4, 0, 0, 0, 0, 0, 0, -4,
    -2, -2, -8, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, -6, 0, -8, -3,
    -5, -12, -2, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -5, -6, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -12, -11, -6, 0, -10, 0, 0,
    0, 0, 0, -6, -10, 0, 0, 0,
    0, -2, -9, -10, -15, -12, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -8, 0, 0,
    -26, -4, -23, -16, 0, -26, 0, 0,
    0, -4, 0, 0, 0, 0, -10, -3,
    -16, -10, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -16, 0, -35, 0, -4, 0, -6, -5,
    -10, -8, -4, -11, -10, 0, 0, 0,
    0, -7, 0, -8, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    -6, 0, -4, -4, -8, -10, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -6, 0, -4, 0, -3, -2,
    0, -6, 0, -3, -4, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -2, 0, -5, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -4, -2, -3, -12, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -26, -7, -33, -5, 0, 0, 0, 0,
    -7, 0, 0, -19, -19, -10, 0, 0,
    -17, -25, -4, -19, -21, -19, -21, -22,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -3, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -22, -7, -30, -2, 0, 0, 0, 0,
    0, 0, 0, -17, -15, -7, 0, 0,
    -15, -14, -4, -14, -6, -6, -8, -8,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -14, -3, -17, -1,
    0, 0, 0, 0, 0, 0, 0, -10,
    -8, -4, 0, 0, -9, -9, -2, -8,
    -6, -6, -8, -8, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, -2, -7, -3, 0, 0,
    0, 0, 0, -2, -7, -4, 0, -2,
    -3, -6, -10, -8, -16, -14, 0, 0,
    -15, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -22, -10, -32, -6,
    0, 0, 0, 0, 0, 0, 0, -29,
    -27, -10, 0, 0, -29, -25, -12, -27,
    -19, -18, -20, -21, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, -6, -6, -8, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 15, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -18, 0, -16, -10,
    -3, -30, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -2, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    -19, 0, -15, -8, -7, -27, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -2, -8, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -19, 0, -9, -7,
    -3, -23, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -19, 0, -12, -7, -6, -22, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -1, -2, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -11, 0, -13, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -3, 0, 0, 0,
    0, -3, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, 0, -15, -10, 0, -27, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -28, -2, -9, -6,
    0, -15, 0, -2, -6, 0, 0, -1,
    0, -3, -3, -4, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    -2, -1, 0, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -17, 0, 0, 0,
    -16, -14, -10, -4, -3, 0, 0, 0,
    0, -2, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -24, 0, -10, -8, -6, -23, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -4, -2,
    0, -10, 0, 0, -2, 0, 0, 0,
    0, -1, 0, -1, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, -18, 0,
    -21, 0, -6, -6, -16, -19, -10, -2,
    -4, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, -13, 0, -19, 0, -6, -6,
    -14, -18, -8, -2, -2, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    -21, 0, -8, -8, 0, -20, 0, -3,
    -8, 0, 0, -2, 0, -4, 0, -2,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -21, 0, -6, -9,
    0, -21, 0, 0, -4, 0, 0, 0,
    0, -2, 0, -2, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 48,
    .right_class_cnt     = 36,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t mi_demi_12 = {
#else
lv_font_t mi_demi = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if MI_DEMI*/

