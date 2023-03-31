//
// Created by Gordon on 2022/11/25.
//

#ifndef PLANTSIO_IVY_UI__H
#define PLANTSIO_IVY_UI__H

#include "Base.h"
#include "Anim/ui/tools.h"

#include "Anim/ui/UIProgress.h"
#include "Anim/ui/UISysInfo.h"
#include "Anim/ui/UIFluid.h"
#include "Anim/ui/UIFluidAssist.h"
#include "Anim/ui/UIWeather.h"
#include "Anim/ui/UITime.h"
#include "Anim/ui/UIDate.h"
#include "Anim/ui/UIDoubleProgress.h"
#include "Anim/ui/UIActionBox.h"
#include "Anim/ui/UIQrCode.h"
#include "Anim/ui/UILoading.h"
#include "Anim/ui/UIPlantStatus.h"
#include "Anim/ui/UITest.h"
#include "Anim/ui/UIText.h"
#include "Anim/ui/UIBoot.h"
#include "Anim/ui/TutorialUI.h"
#include "Anim/ui/UIDebug.h"
#include "Anim/ui/UITestError.h"
#include "Anim/ui/UITestAging.h"
#include "Anim/ui/UIOffline.h"
#include "Anim/ui/UINoService.h"

namespace UI {

    typedef std::function<std::shared_ptr<UI::Base>()> UIBuilder;

    std::unordered_map<int, UIBuilder> &get_builders();

    template<typename T>
    UIBuilder create_ui_builder(index_t index) {
        return [index]() {
            //std::lock_guard<std::recursive_timed_mutex> _lock(IvyAnim::instance().get_mutex());
            auto ui = std::make_shared<T>();
            ui->set_index(index);
            return ui;
        };
    }

    template<typename T>
    void register_ui(index_t index) {
        get_builders().insert({index, create_ui_builder<T>(index)});
    }

    template<typename T>
    std::shared_ptr<T> build_ui(int index) {
        auto builder = get_builders().find(index);
        if (builder != get_builders().end()) {
            auto ui = std::dynamic_pointer_cast<T>(builder->second());
            if (ui != nullptr) {
                return ui;
            }
        }
        return nullptr;
    }
}
#endif //PLANTSIO_IVY_UI__H
