//
// Created by Gordon on 2021/8/13.
//

#ifndef PLANTSIO_IVY_UIBASE_H
#define PLANTSIO_IVY_UIBASE_H

#include "lvgl/lvgl.h"

enum UI_index {
    UI_NULL = -1,
    UI_NONE = 0,
    UI_PROGRESS,
    UI_DOUBLE_PROGRESS,
    UI_FLUID,
    UI_WEATHER,
    UI_TIME,
    UI_DATE,
    UI_SYS_INFO,
    UI_ACTION,
    UI_LOADING,
};
enum UI_INPUT {
    UI_INPUT_LEFT = 0,
    UI_INPUT_RIGHT,
};

class UISiblings {
public:
    explicit UISiblings(UI_index left = UI_NULL, UI_index right = UI_NULL, UI_index next = UI_NULL) : left(left),
                                                                                                      right(right),
                                                                                                      next(next) {};
    UI_index left;
    UI_index right;
    UI_index next;
};

class UIBase {
public:
    UIBase();

    ~UIBase();

//    lv_obj_t *scr;

//    bool active() {
//        /* todo add more pre-conditions */
//        return (lv_scr_act() == scr);
//    }
    virtual UI_index get_index() {
        return UI_NULL;
    }

    virtual void show();

    virtual void hide();

    virtual void clear();

    virtual void routine();

    void set_siblings(UISiblings siblings) {
        m_siblings = siblings;
    }

    UISiblings get_siblings() {
        return m_siblings;
    }

    void set_start(bool start = true) {
        m_start = start;
    }

    bool started() const {
        return m_start;
    }

protected:
    UISiblings m_siblings;
    bool m_start = false;
};

class UIDefault : public UIBase {
    UI_index get_index() override {
        return UI_NONE;
    }

    bool started() const{
        return true;
    }

};

#endif //PLANTSIO_IVY_UIBASE_H
