//
// Created by sungaoran on 2021/11/16.
//

#ifndef PLANTSIO_IVY_UIPROGRESS_H
#define PLANTSIO_IVY_UIPROGRESS_H

#include "UIBase.h"

class UIProgress : public UIBase{
public:
    void show() override;

    void update(const char* title,const char* status,uint8_t progress);

    void set_title(const char* value);

    void set_status(const char* value);

    void set_progress(uint8_t progress);

private:
    lv_obj_t * m_bar;
    lv_obj_t * m_title_label;
    lv_obj_t * m_status_label;
    lv_style_t style_bg;
    lv_style_t style_indic;
};


#endif //PLANTSIO_IVY_UIPROGRESS_H
