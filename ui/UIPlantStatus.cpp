//
// Created by Gordon on 2022/4/15.
//

#include "UIPlantStatus.h"
#include "tools.h"

namespace UI {
    StatusCard::StatusCard(lv_obj_t *parent, const char *name, const char *unit) {
        m_card = lv_obj_create(parent);
        lv_obj_set_size(m_card, DEFAULT_CARD_W, DEFAULT_CARD_H);
        lv_obj_set_style_bg_opa(m_card, LV_OPA_TRANSP, 0);
        lv_obj_clear_flag(m_card, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_radius(m_card, 30, 0);

        m_value_label = lv_label_create(m_card);
        update_value_label("90");

        m_name_label = lv_label_create(m_card);
        lv_label_set_text(m_name_label, name);
        lv_obj_align(m_name_label, LV_ALIGN_BOTTOM_MID, 0, -10);
        lv_obj_set_style_text_font(m_name_label, &ba_16, 0);
        lv_obj_set_style_text_color(m_name_label, lv_color_white(), 0);

        m_unit_label = lv_label_create(m_card);
        lv_label_set_text(m_unit_label, unit);
        lv_obj_align_to(m_unit_label, m_name_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_obj_set_style_text_font(m_unit_label, &ba_16, 0);
        lv_obj_set_style_text_color(m_unit_label, lv_color_white(), 0);
    }

    void StatusCard::update_value_label(const char *value_str) {
        /* todo should adjust font size according to value string length */
        lv_label_set_text(m_value_label, value_str);
        lv_obj_set_style_text_font(m_value_label, &ba_40, 0);
        lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_set_style_text_color(m_value_label, lv_color_white(), 0);
    }

    ChatBubble::ChatBubble(lv_obj_t *parent, lv_coord_t bubble_w, lv_coord_t bubble_h, lv_coord_t pointer_w,
                           lv_coord_t pointer_h)
            : m_space(lv_obj_create(parent)),
              m_pointer(m_space, pointer_w, pointer_h) {
        lv_obj_remove_style_all(m_space);
        lv_obj_set_size(m_space, bubble_w, bubble_h + pointer_h * 2);

        m_card = lv_obj_create(m_space);
        lv_obj_set_style_radius(m_card, 20, 0);
        lv_obj_set_style_bg_opa(m_card, LV_OPA_TRANSP, 0);
        lv_obj_set_size(m_card, bubble_w, bubble_h);
        lv_obj_align(m_card, LV_ALIGN_CENTER, 0, 0);

        m_label = lv_label_create(m_card);
        lv_obj_set_style_text_color(m_card, lv_color_white(), 0);

        update_pointer_location(20, true);
        update_color(lv_color_white());
        lv_obj_move_foreground(m_pointer.body);
    }

    void ChatBubble::update_pointer_location(int x, bool up) {
        if (up) {
            lv_obj_align_to(m_pointer.body, m_card, LV_ALIGN_OUT_TOP_LEFT, x, 2);
        } else {
            lv_obj_align_to(m_pointer.body, m_card, LV_ALIGN_OUT_BOTTOM_LEFT, x, -3);/* FIXME*/
        }
        m_pointer.set_direction(up);
    }

    void ChatBubble::update_color(lv_color_t color) {
        m_pointer.update_color(color);
        lv_obj_set_style_border_color(m_card, color, 0);
    }

    void ChatBubble::update_content(const char *content) {
        lv_label_set_text(m_label, content);
    }

    void ChatBubble::set_visible(bool show) {
        if (show) {
            lv_obj_clear_flag(m_space, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(m_space, LV_OBJ_FLAG_HIDDEN);
        }
        visible = show;
    }

    BubblePointer::BubblePointer(lv_obj_t *parent, lv_coord_t pointer_w, lv_coord_t pointer_h, lv_coord_t line_w)
            : m_pointer_h(pointer_h),
              m_pointer_w(pointer_w),
              m_line_w(line_w) {
        body = lv_obj_create(parent);
        lv_obj_remove_style_all(body);
        line_bottom = lv_line_create(body);
        line_top = lv_line_create(body);
        lv_obj_set_size(body, pointer_w, pointer_h);
        lv_obj_set_style_line_width(line_top, line_w, 0);
        lv_obj_set_style_line_width(line_bottom, line_w, 0);
        set_direction(true);
    }

    void BubblePointer::update_color(lv_color_t color) {
        lv_obj_set_style_line_color(line_top, color, 0);
        lv_obj_set_style_line_color(line_bottom, lv_color_black(), 0);
    }

    void BubblePointer::set_direction(bool up) {
        if (up) {
            lv_line_set_y_invert(line_top, false);
            lv_line_set_y_invert(line_bottom, false);
            points_top = {{0,                              (lv_coord_t) (m_pointer_h - m_line_w / 2)},
                          {(lv_coord_t) (m_pointer_w / 2), (lv_coord_t) (m_line_w / 2)},
                          {m_pointer_w,                    (lv_coord_t) (m_pointer_h - m_line_w / 2)}};
            points_bottom = {{0,                          (lv_coord_t) (m_pointer_h - m_line_w / 2)},
                             {(lv_coord_t) (m_pointer_w), (lv_coord_t) (m_pointer_h - m_line_w / 2)}};
        } else {
            lv_line_set_y_invert(line_top, true);
            lv_line_set_y_invert(line_bottom, true);
            points_top = {{0,                              (lv_coord_t) (m_pointer_h - m_line_w / 2 - 1)},
                          {(lv_coord_t) (m_pointer_w / 2), (lv_coord_t) (m_line_w / 2)},
                          {m_pointer_w,                    (lv_coord_t) (m_pointer_h - m_line_w / 2 - 1)}};
            points_bottom = {{0,                          (lv_coord_t) (m_pointer_h - m_line_w / 2 - 1)},
                             {(lv_coord_t) (m_pointer_w), (lv_coord_t) (m_pointer_h - m_line_w / 2 - 1)}};

        }
        lv_line_set_points(line_top, points_top.data(), 3);
        lv_line_set_points(line_bottom, points_bottom.data(), 2);
    }


    UIPlantStatus::UIPlantStatus()
            : Base(),
              top_area(lv_obj_create(m_scr)),
              bottom_area(lv_obj_create(m_scr)),
              bubble(m_scr, DEFAULT_AREA_W, BUBBLE_HEIGHT, BUBBLE_POINTER_W, BUBBLE_POINTER_H),
              card_temp(top_area, "temp", "°C"),
              card_humidity(top_area, "humidity", "%"),
              card_soil(top_area, "soil", "%"),
              card_water(bottom_area, "water", "mL"),
              card_battery(bottom_area, "battery", "%"),
              card_light(bottom_area, "light", "lx") {
        lv_obj_set_scrollbar_mode(m_scr, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_style_pad_ver(m_scr,DEFAULT_PADDING_H,0);

        lv_obj_remove_style_all(top_area);
        lv_obj_remove_style_all(bottom_area);
        lv_obj_clear_flag(top_area, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(bottom_area, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(top_area, DEFAULT_AREA_W, DEFAULT_CARD_H);
        lv_obj_set_size(bottom_area, DEFAULT_AREA_W, DEFAULT_CARD_H);

        lv_obj_set_flex_flow(top_area, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(top_area, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
        lv_obj_set_style_pad_all(top_area,0,0);

        lv_obj_set_flex_flow(bottom_area, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(bottom_area, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY);
        lv_obj_set_style_pad_all(bottom_area,0,0);

        lv_obj_align(top_area, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_align(bubble.m_space, LV_ALIGN_TOP_MID, 0, DEFAULT_CARD_H);
        lv_obj_align(bottom_area, LV_ALIGN_TOP_MID, 0, DEFAULT_CARD_H + DEFAULT_PADDING_H);
        bubble.set_visible(false);
    }

    static void anim_set_align(void *var, int32_t value) {
        lv_obj_align((lv_obj_t *) var, LV_ALIGN_TOP_MID, 0, value);
    }

    static void bubble_show_cb(struct _lv_anim_t *anim) {
        auto *bubble = static_cast<ChatBubble *>(anim->user_data);
        bubble->set_visible(true);
        auto a = anim_create(bubble->m_space, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 500);
        lv_anim_start(&a);
    }

    void UIPlantStatus::hide_bubble_cb() {
        bubble.set_visible(false);
        lv_obj_align(bottom_area, LV_ALIGN_TOP_MID, 0, DEFAULT_CARD_H + DEFAULT_PADDING_H);
        lv_obj_scroll_to_y(m_scr, lv_obj_get_y(top_area) - DEFAULT_PADDING_H, LV_ANIM_OFF);
    }


    static void bubble_hide_cb(struct _lv_anim_t *anim) {
        auto *ui = static_cast<UIPlantStatus *>(anim->user_data);
        ui->hide_bubble_cb();
    }

    void UIPlantStatus::update_bubble_status(const char *content, lv_color_t color, lv_coord_t x, bool up, bool show) {
        if (show) {
            bubble.update_pointer_location(x, up);
            bubble.update_color(color);
            bubble.update_content(content);
            if (!bubble.visible) {
                auto a = anim_create(bottom_area, anim_set_align, DEFAULT_CARD_H + DEFAULT_PADDING_H,
                                     DEFAULT_CARD_H + BUBBLE_HEIGHT + BUBBLE_POINTER_H * 2, 300, 0, 0, 0,
                                     bubble_show_cb,
                                     &bubble);
                lv_anim_start(&a);
            }
            if (up != focus_top) {
                if (up) {
                    lv_obj_scroll_to_y(m_scr, lv_obj_get_y(top_area) - DEFAULT_PADDING_H, LV_ANIM_OFF);
                } else {
                    lv_obj_scroll_to_y(m_scr, lv_obj_get_y(bottom_area) + DEFAULT_PADDING_H, LV_ANIM_OFF);
                }
                focus_top = up;
            }
        } else {
            if (bubble.visible) {
                auto a = anim_create(bubble.m_space, anim_fade, LV_OPA_COVER, LV_OPA_TRANSP, 500, 0, 0, 0,
                                     bubble_hide_cb,
                                     this);
                lv_anim_start(&a);
            }
        }
    }

    void UIPlantStatus::routine() {
        Base::routine();
        static int i = 0;
        if (i++ > 20) {
            select_next();
            i = 0;
        }
    }

    void UIPlantStatus::select_index(int index) {
        if (index == current_index) {
            return;
        }
        if (index == -1) {
            update_bubble_status("", lv_color_white(), 0, false, false);
        } else {
            bool up;
            if (index < 3) {
                up = true;
            } else {
                up = false;
            }
            update_bubble_status(get_content_by_index(index).c_str(), get_color_by_index(index),
                                 get_pointer_x_by_index(index), up, true);
        }
        current_index = index;
    }

    void UIPlantStatus::select_next() {
        if (current_index == 5) {
            select_index(-1);
        } else {
            select_index(current_index + 1);
        }
    }

    lv_coord_t UIPlantStatus::get_pointer_x_by_index(int index) {
        int seq = index % 3;
        if (seq == 0) {
            return (DEFAULT_CARD_W - BUBBLE_POINTER_W) / 2;
        } else if (seq == 1) {
            return DEFAULT_AREA_W / 2 - BUBBLE_POINTER_W / 2;
        } else {
            return DEFAULT_AREA_W - (DEFAULT_CARD_W + BUBBLE_POINTER_W) / 2;
        }
    }

    std::string UIPlantStatus::get_content_by_index(int index) {
        return "test";  /* todo */
    }

    lv_color_t UIPlantStatus::get_color_by_index(int index) {
        return lv_color_white();
    }
}