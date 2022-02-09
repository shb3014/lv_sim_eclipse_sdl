//
// Created by Gordon on 2021/8/13.
//

#ifndef PLANTSIO_IVY_UIBASE_H
#define PLANTSIO_IVY_UIBASE_H

#include "lvgl/lvgl.h"

class UIBase {
public:
    UIBase();

    ~UIBase();

//    lv_obj_t *scr;

//    bool active() {
//        /* todo add more pre-conditions */
//        return (lv_scr_act() == scr);
//    }

    virtual void show();

    virtual void hide();

    virtual void clear();

    virtual void routine();

protected:
    bool initialized = false;
};


#endif //PLANTSIO_IVY_UIBASE_H
