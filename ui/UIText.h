//
// Created by sungaoran on 2022/5/4.
//

#ifndef LVGL_UITEXT_H
#define LVGL_UITEXT_H

#include "Base.h"
#include "string"
#include "Components.h"

namespace UI {
    class UIText : public Base {
    public:
        UIText();

        index_t get_index() override {
            return UI_TEXT;
        }

        void update(const char *main, const char *sub, bool anim_on = true);

        void update_main(const char *main, bool anim_on = true);

        void update_sub(const char *sub, bool anim_on = true);

        void realign();

    private:
        BasicText m_text_main;
        BasicText m_text_sub;
    };
}

#endif //LVGL_UITEXT_H
