//
// Created by Gordon on 2022/3/15.
//

#ifndef LVGL_UIQRCODE_H
#define LVGL_UIQRCODE_H

#include "UIBase.h"

#define QR_CODE_MAX_LEN             180
#define QR_CODE_Y_OFFSET            13
#define QR_CODE_MARGIN_IN           15
#define QR_CODE_RADIUS              12

class UIQrCode : public UIBase {
public:

    UIQrCode();

    UI_index get_index() override{
        return UI_QR;
    }

    void start_routine() override;

    void update_qr(const char *qr_content);

    void update_desc(const char *desc);

    void clear() override;

private:
    lv_obj_t *qr_canvas;
    lv_obj_t *qr_rect;
    lv_obj_t *desc_label;
};


#endif //LVGL_UIQRCODE_H
