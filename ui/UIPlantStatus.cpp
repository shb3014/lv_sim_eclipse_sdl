//
// Created by Gordon on 2022/4/15.
//

#include "UIPlantStatus.h"
#include "tools.h"
#include "tool/sys.h"

#ifndef LV_SIM

#include "Engine/Public.h"

#endif

namespace UI {
    StatusCard::StatusCard(lv_obj_t *parent, const char *name, const char *unit, lv_color_t name_color) {
        m_card = lv_obj_create(parent);
        lv_obj_set_size(m_card, DEFAULT_CARD_W - 2, DEFAULT_CARD_H - 2);
        lv_obj_set_style_bg_opa(m_card, LV_OPA_TRANSP, 0);
        lv_obj_clear_flag(m_card, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_radius(m_card, 20, 0);

        m_value_label = lv_label_create(m_card);
        update_value_label("--");

        m_name_label = lv_label_create(m_card);
        lv_label_set_text(m_name_label, name);
        lv_obj_align(m_name_label, LV_ALIGN_BOTTOM_MID, 0, -10);
        lv_obj_set_style_text_font(m_name_label, &ba_16, 0);
        lv_obj_set_style_text_color(m_name_label, name_color, 0);

        m_unit_label = lv_label_create(m_card);
        lv_label_set_text(m_unit_label, unit);
        lv_obj_align_to(m_unit_label, m_name_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_obj_set_style_text_font(m_unit_label, &ba_16, 0);
        lv_obj_set_style_text_color(m_unit_label, lv_color_white(), 0);
    }

    void StatusCard::update_value_label(const std::string &value_str) {
        /* todo should adjust font size according to value string length */
        if (value_str != std::string(lv_label_get_text(m_value_label))) {
            lv_label_set_text(m_value_label, value_str.c_str());
            if (value_str.length() >= 5) {
                lv_obj_set_style_text_font(m_value_label, &ba_16, 0);
            lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 14);
            } else if (value_str.length() > 3) {
                lv_obj_set_style_text_font(m_value_label, &ba_30, 0);
                lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 10);
            } else {
                lv_obj_set_style_text_font(m_value_label, &ba_40, 0);
                lv_obj_align(m_value_label, LV_ALIGN_TOP_MID, 0, 6);
            }
            lv_obj_set_style_text_color(m_value_label, lv_color_white(), 0);
        }
    }

    void StatusCard::update_selected_style(bool selected) const {
        lv_obj_set_style_border_width(m_card, 2 + selected, 0);
        lv_obj_set_size(m_card, DEFAULT_CARD_W + 2 * selected - 2, DEFAULT_CARD_H + 2 * selected - 2);
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
    }

    CardArea::CardArea(lv_obj_t *parent, lv_coord_t pos_init, lv_coord_t pos_offset) :
            m_area(lv_obj_create(parent)),
            m_pos_init(pos_init),
            m_pos_offset(pos_offset) {
        lv_obj_remove_style_all(m_area);
        lv_obj_clear_flag(m_area, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(m_area, DEFAULT_AREA_W, DEFAULT_CARD_H);

        lv_obj_set_flex_flow(m_area, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(m_area, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_SPACE_EVENLY,
                              LV_FLEX_ALIGN_SPACE_EVENLY);
        lv_obj_set_style_pad_all(m_area, 0, 0);
        lv_obj_align(m_area, LV_ALIGN_TOP_MID, 0, m_pos_init);
    }

    void CardArea::move_away() const {
        lv_obj_align(m_area, LV_ALIGN_TOP_MID, 0, m_pos_offset);
    }

    void CardArea::move_away(lv_anim_ready_cb_t cb, void *user_data) const {
        auto a = anim_create(m_area, anim_set_align_top, m_pos_init, m_pos_offset, 300, 0, 0, 0, cb, user_data);
        lv_anim_start(&a);
    }

    void CardArea::move_back() const {
        lv_obj_align(m_area, LV_ALIGN_TOP_MID, 0, m_pos_init);
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

    static void status_update_timer_cb(lv_timer_t *timer) {
        auto ui = static_cast<UIPlantStatus *>(timer->user_data);
#ifdef LV_SIM
        ui->get_card_by_index(UIPlantStatus::light).update_value_label("23024");
        ui->get_card_by_index(UIPlantStatus::temp).update_value_label("25");
        ui->get_card_by_index(UIPlantStatus::humidity).update_value_label("100");
        ui->get_card_by_index(UIPlantStatus::soil).update_value_label("100");
        ui->get_card_by_index(UIPlantStatus::water).update_value_label("110");
        ui->get_card_by_index(UIPlantStatus::battery).update_value_label("45");
#else
        ui->get_card_by_index(UIPlantStatus::light).update_value_label(
                std::to_string(Prop::get<int>(Prop::ambient_light)));
        ui->get_card_by_index(UIPlantStatus::temp).update_value_label(
                double_to_string(Prop::get<double>(Prop::temperature), 1));
        ui->get_card_by_index(UIPlantStatus::humidity).update_value_label(
                std::to_string(Prop::get<int>(Prop::humidity)));
        ui->get_card_by_index(UIPlantStatus::soil).update_value_label(
                std::to_string(Prop::get<int>(Prop::soil_moisture)));
        ui->get_card_by_index(UIPlantStatus::water).update_value_label(
                std::to_string(Prop::get<int>(Prop::water_level)));
        ui->get_card_by_index(UIPlantStatus::battery).update_value_label(
                std::to_string(Prop::get<int>(Prop::battery_percent)));
#endif
    }


    UIPlantStatus::UIPlantStatus()
            : Base(),
              top_area(m_scr, 0, DEFAULT_PADDING_H - BUBBLE_AREA_H),
              bottom_area(m_scr, DEFAULT_CARD_H + DEFAULT_PADDING_H,
                          DEFAULT_CARD_H + BUBBLE_AREA_H),
              bubble(m_scr, DEFAULT_AREA_W, BUBBLE_HEIGHT, BUBBLE_POINTER_W, BUBBLE_POINTER_H),
              m_cards({
                              StatusCard(top_area.m_area, "light", "lx", lv_color_make(249, 209, 113)),
                              StatusCard(top_area.m_area, "temp", "°C", lv_color_make(255, 97, 97)),
                              StatusCard(top_area.m_area, "humidity", "%", lv_color_make(154, 215, 253)),
                              StatusCard(bottom_area.m_area, "soil", "%", lv_color_make(192, 160, 132)),
                              StatusCard(bottom_area.m_area, "water", "mL", lv_color_make(154, 215, 253)),
                              StatusCard(bottom_area.m_area, "battery", "%", lv_color_make(123, 214, 89))
                      }) {

        lv_obj_set_scrollbar_mode(m_scr, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_style_pad_ver(m_scr, DEFAULT_PADDING_H, 0);
        m_value_update_timer = lv_timer_create(status_update_timer_cb, 500, this);
        lv_timer_set_repeat_count(m_value_update_timer, -1);
        hide_bubble_cb();
    }

    static void _show_bubble_cb(struct _lv_anim_t *anim) {
        auto *ui = static_cast<UIPlantStatus *>(anim->user_data);
        ui->show_bubble_cb();
    }

    void UIPlantStatus::move_bubble() {
        lv_obj_align_to(bubble.m_space, top_area.m_area, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    }

    void UIPlantStatus::show_bubble_cb() {
        move_bubble();
        bubble.set_visible(true);
        auto a = anim_create(bubble.m_space, anim_fade, LV_OPA_TRANSP, LV_OPA_COVER, 500);
        lv_anim_start(&a);
    }

    void UIPlantStatus::hide_bubble_cb() {
        bubble.set_visible(false);
        top_area.move_back();
        bottom_area.move_back();
        set_focus(no_selection);
    }


    static void bubble_hide_cb(struct _lv_anim_t *anim) {
        auto *ui = static_cast<UIPlantStatus *>(anim->user_data);
        ui->hide_bubble_cb();
    }

    void UIPlantStatus::update_bubble_status(const char *content, lv_color_t color, lv_coord_t x) {
        if (current_area_select != no_selection) {
            /* bubble should be visible */
            bubble.update_pointer_location(x, current_area_select == top_selected);
            bubble.update_color(color);
            bubble.update_content(content);
        }

        if (current_area_select != last_area_select) {
            /* focus should be shifted */
            if (last_area_select != no_selection) {
                /* bubble was visible */
                if (current_area_select == no_selection) {
                    /* hide bubble */
                    auto a = anim_create(bubble.m_space, anim_fade, LV_OPA_COVER, LV_OPA_TRANSP, 300, 0, 0, 0,
                                         bubble_hide_cb,
                                         this);
                    lv_anim_start(&a);
                } else {
                    /* simply shift focus */
                    set_focus(current_area_select);
                }
            } else {
                /* bubble was not visible */
                if (current_area_select == top_selected) {
                    bottom_area.move_away(_show_bubble_cb, this);
                } else {
                    top_area.move_away(_show_bubble_cb, this);
                }
            }
        }
    }

    void UIPlantStatus::routine() {
#ifdef LV_SIM
        Base::routine();
        static int i = 0;
        if (i++ > 20) {
            select_next();
//            select_last();
            i = 0;
        }
#endif
    }

    void UIPlantStatus::update_selection_cb(int index) {
        /* update bubble contents, color, and pointer pos */
        update_bubble_status(get_content_by_index(index).c_str(), get_name_color_by_index(index),
                             get_pointer_x_by_index(index));
        /* update card style */
        if (current_index != -1) {
            /* should rm last card style */
            get_card_by_index((sensor_index_t) current_index).update_selected_style(false);
        }
        if (index != -1) {
            get_card_by_index((sensor_index_t) index).update_selected_style(true);
        }
        current_index = index;
    }

    void UIPlantStatus::select_index(int index) {
        if (index == current_index) {
            return;
        }
        last_area_select = current_area_select;
        if (index == -1) {
            current_area_select = no_selection;
        } else {
            if (index < 3) {
                current_area_select = top_selected;
            } else {
                current_area_select = bottom_selected;
            }
        }
        update_selection_cb(index);
    }

    void UIPlantStatus::select_next() {
        if (current_index == 5) {
            select_index(-1);
        } else {
            select_index(current_index + 1);
        }
    }

    void UIPlantStatus::select_last() {
        if (current_index > -1) {
            select_index(current_index - 1);
        } else {
            select_index(5);
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

    lv_color_t UIPlantStatus::get_name_color_by_index(int index) {
        return lv_color_white();
    }

    void UIPlantStatus::set_focus(area_select_t t_focus) {
        switch (t_focus) {
            case top_selected:
                top_area.move_back();
                bottom_area.move_away();
                move_bubble();
                break;
            case no_selection:
                top_area.move_back();
                bottom_area.move_back();
                break;
            case bottom_selected:
                bottom_area.move_back();
                top_area.move_away();
                move_bubble();
                break;
        }
    }

    void UIPlantStatus::input_cb(input_t input) {
        Base::input_cb(input);
        if (input == UI_INPUT_LEFT) {
            select_last();
        } else if (input == UI_INPUT_RIGHT) {
            select_next();
        }
    }

    void UIPlantStatus::clear() {
        lv_timer_del(m_value_update_timer);
        Base::clear();
    }
}