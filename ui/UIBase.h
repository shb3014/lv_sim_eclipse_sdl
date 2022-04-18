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
    UI_PLANT_STATUS,
    UI_QR,

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
    /* every derived UI class shall implement its obj creation in constructor */
    UIBase();

    ~UIBase();

    /* every derived UI class must implement this method and register in the driver load method */
    virtual UI_index get_index() = 0;

    /* clear animations and timers here */
    virtual void clear();

    /* called every frame */
    virtual void routine();

    /* bound to touch events */
    virtual void input_cb(UI_INPUT input);

    //region non-virtual members
    /* set ui switching behavior todo use a global ui matrix instead */
    void set_siblings(UISiblings siblings) {
        m_siblings = siblings;
    }

    UISiblings get_siblings() {
        return m_siblings;
    }

    void set_start(bool start = true) {
        m_start = start;
        if (start && m_scr) {
            lv_scr_load(m_scr);
            start_routine();
        }
    }

    bool started() const {
        return m_start;
    }

    lv_obj_t *get_scr() {
        return m_scr;
    }
    //endregion

protected:
    /* animations and timers should be created and started here */
    virtual void start_routine(){}

    UISiblings m_siblings;
    lv_obj_t *m_scr;
    bool m_start = false;
};

/* Default empty UI class */
class UIDefault : public UIBase {
    using UIBase::UIBase;

    UI_index get_index() override {
        return UI_NONE;
    }

    bool started() const {
        return true;
    }

};

#endif //PLANTSIO_IVY_UIBASE_H
