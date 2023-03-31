
#ifndef MI_PLANTS_IVY_LANGUAGEDEFINE_H
#define MI_PLANTS_IVY_LANGUAGEDEFINE_H

namespace Lang {
    typedef enum {
        zh = 0, /* Chinese */ 
        en = 1, /* English */ 
        jp = 2, /* Japanese */ 
        lang_max
    } lang_t;
    
    enum font_t {
        mi_ex_font_120,
        mi_light_font_14,
        mi_light_font_16,
        mi_light_font_24,
        mi_light_font_30,
        mi_light_font_36,
        mi_light_font_109,
        ba_font_16,
        ba_font_30,
        ba_font_40,
        ba_font_120,
        jp_font_14,
        jp_font_16,
        jp_font_24,
        jp_font_30,
        jp_font_36,
        jp_font_120,
        font_max,
    };
    
    struct lang_desc {
        font_t zh;
        font_t en;
        font_t jp;
    };
}

#endif //MI_PLANTS_IVY_LANGUAGEDEFINE_H