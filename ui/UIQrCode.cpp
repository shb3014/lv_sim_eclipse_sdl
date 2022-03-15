//
// Created by Gordon on 2022/3/15.
//

#include "UIQrCode.h"
#include "tool/qrcodegen.hpp"

#include "drivers/common.h" /* fixme */
#include "tools.h" /* fixme */

void UIQrCode::show() {
    qr_rect = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_color(qr_rect, lv_color_white(), 0);
    lv_obj_set_size(qr_rect, QR_CODE_MAX_LEN, QR_CODE_MAX_LEN);
    lv_obj_align(qr_rect, LV_ALIGN_CENTER, 0, -QR_CODE_Y_OFFSET);
    lv_obj_set_style_radius(qr_rect, QR_CODE_RADIUS, 0);
    lv_obj_clear_flag(qr_rect, LV_OBJ_FLAG_SCROLLABLE);

    qr_canvas = lv_canvas_create(qr_rect);
    lv_obj_align(qr_canvas, LV_ALIGN_CENTER, 0, 0);
    lv_canvas_set_buffer(qr_canvas, get_canvas_buf(), QR_CODE_MAX_LEN, QR_CODE_MAX_LEN, LV_IMG_CF_TRUE_COLOR);

    desc_label = lv_label_create(lv_scr_act());
    lv_obj_align_to(desc_label, qr_rect, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
    lv_obj_set_style_text_font(desc_label, &ba_16, 0);
    lv_obj_set_style_text_align(desc_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(desc_label, lv_color_white(), 0);
    lv_obj_set_width(desc_label, 300);
    lv_label_set_recolor(desc_label,true);

    lv_anim_t anim = anim_create(desc_label, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 2000, 0, 2500, 1200,
                                 nullptr, nullptr, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&anim);

    UIBase::show();
}

using qrcodegen::QrCode;

void UIQrCode::update_desc(const char *desc) {
    lv_label_set_text(desc_label, desc);
    lv_obj_align_to(desc_label, qr_rect, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
}

void UIQrCode::update_qr(const char *qr_content) {
    const QrCode::Ecc err_level = QrCode::Ecc::MEDIUM;
    const QrCode qr = QrCode::encodeText(qr_content, err_level);
    int multiply = QR_CODE_MAX_LEN / qr.getSize();
    lv_coord_t side = qr.getSize() * multiply;

    lv_obj_set_size(qr_rect, side + QR_CODE_MARGIN_IN, side + QR_CODE_MARGIN_IN);
    lv_obj_align(qr_rect, LV_ALIGN_CENTER, 0, -QR_CODE_Y_OFFSET);

    lv_canvas_set_buffer(qr_canvas, get_canvas_buf(), side, side, LV_IMG_CF_TRUE_COLOR);
    lv_obj_align(qr_canvas, LV_ALIGN_CENTER, 0, 0);

    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.shadow_opa = LV_OPA_TRANSP;
    rect_dsc.outline_opa = LV_OPA_TRANSP;
    rect_dsc.border_width = 0;
    rect_dsc.border_opa = LV_OPA_TRANSP;
    rect_dsc.bg_color = lv_color_white();
    lv_canvas_draw_rect(qr_canvas, 0, 0, side, side, &rect_dsc);
    rect_dsc.bg_color = lv_color_black();

    for (int qr_y = 0; qr_y < qr.getSize(); qr_y++) {
        for (int qr_x = 0; qr_x < qr.getSize(); qr_x++) {
            if (qr.getModule(qr_x, qr_y)) {
                lv_canvas_draw_rect(qr_canvas, qr_x * multiply, qr_y * multiply, multiply, multiply, &rect_dsc);
            }
        }
    }
}