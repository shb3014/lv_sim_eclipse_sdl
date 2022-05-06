
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */

#include <stdlib.h>
#include <unistd.h>

#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/

#include "SDL2/SDL.h"
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lv_demos/lv_demo.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mousewheel.h"

#include "ui/UIWeather.h"
#include "ui/UITime.h"
#include "ui/UIDate.h"
#include "ui/UIProgress.h"
#include "ui/UIDoubleProgress.h"
#include "ui/UIActionBox.h"
#include "ui/UILoading.h"
#include "ui/UIQrCode.h"
#include "ui/UIPlantStatus.h"
#include "ui/UITest.h"
#include "ui/UIText.h"
#include "ui/TutorialUI.h"
#include "utils/log.h"
#include "lv_conf.h"
#include "chrono"
#include "memory"
#include "thread"
#include "mutex"
#include "ui/tools.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);

static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/


std::shared_ptr<UI::Base> current_ui;
std::recursive_mutex ui_mutex;

void vTaskDelay(int t) {
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

void ui_thread() {
    printf("ui start\n");
//    auto ui = std::make_shared<UI::TuIntro>();
    auto ui = std::make_shared<UI::TuTouchBar>();
    {
        std::lock_guard<std::recursive_mutex> lock(ui_mutex);
        current_ui = ui;
        ui->set_start(true);
    }
}

int main(int argc, char **argv) {
    (void) argc; /*Unused*/
    (void) argv; /*Unused*/

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();
    current_ui = std::make_shared<UI::UIDefault>();

//  lv_example_switch_1();
//  lv_example_calendar_1();
//  lv_example_btnmatrix_2();
//  lv_example_checkbox_1();
//  lv_example_colorwheel_1();
//  lv_example_chart_6();
//  lv_example_table_2();
//  lv_example_scroll_2();
//  lv_example_textarea_1();
//  lv_example_msgbox_1();
//  lv_example_dropdown_2();
//  lv_example_btn_1();
//  lv_example_scroll_1();
//  lv_example_tabview_1();
//  lv_example_tabview_1();
//  lv_example_flex_3();
//  lv_example_label_1();
//    UIWeather ui;
//    UIQrCode ui;
//    UI::UITime ui;
//    UI::UIProgress ui;
//    UIDoubleProgress ui;
//    UIDate ui;
//    UIActionBox ui;
//    ui.update("Evolve", "Ivy is able to evolve, do you want to update now?", "Yes", "No", []() { log_d("left set"); },
//              []() { log_d("right set"); },60);
//    UILoading ui;
//    UI::UIPlantStatus ui;
//    UI::UITest ui;
//    ui.update_step("1. WiFi Test");
//    ui.update_progress(40,5000);
//    ui.update_desc("connecting");
//    ui.update_value("");
//    ui.set_start(true);
//    UI::UIText ui;
//    ui.set_start(true);
//    ui.update_qr("https://smartapp.tuya.com/s/p?p=9sq9uydcv0aggmh5&uuid=6caca3de5cc488ef943wlm&v=2.0");
//    ui.update_desc("Scan with #DB0000 Tuya# to activate");
//    ui.update_qr("ver: v1, name: ivy1231241, pop: 123141, transport: softap");
//    ui.update_desc("Scan with #DB0000 ESP32 SoftAP# to provision");
//    ui.update("Checking Updates", "requesting from plantsio server");
//    lv_demo_widgets();
//    lv_scr_load(lv_scr_act());
    log_i("main start");
    std::thread thread_ui(ui_thread);

//    ui.update("Progress Test","upgrading",30);
//    ui.update("Evolving","downloading /assets/test.txt",30,"total",10);

    while (true) {
        auto start = std::chrono::steady_clock::now();
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        {
            std::lock_guard<std::recursive_mutex> lock(ui_mutex);
            current_ui->routine();
            lv_timer_handler();
        }
        auto end = std::chrono::steady_clock::now();
        uint32_t frame_t = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double target_t = 1;
        if ((double) frame_t < 41.6) {
            target_t = 41.6 - (double) frame_t;
        }
        vTaskDelay(target_t);
//        usleep((int) (target_t * 1000));
    }

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void) {
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();
    /* Tick init.
     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
     * how much time were elapsed Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);

    /*Create a display buffer*/
    static lv_disp_draw_buf_t disp_buf1;
    static lv_color_t buf1_1[MONITOR_HOR_RES * 100];
    static lv_color_t buf1_2[MONITOR_HOR_RES * 100];
    lv_disp_draw_buf_init(&disp_buf1, buf1_1, buf1_2, MONITOR_HOR_RES * 100);

    /*Create a display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    disp_drv.hor_res = MONITOR_HOR_RES;
    disp_drv.ver_res = MONITOR_VER_RES;
    disp_drv.antialiasing = 1;

    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);

//    lv_theme_t *th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
//                                           LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
//    lv_disp_set_theme(disp, th);

    lv_group_t *g = lv_group_create();
    lv_group_set_default(g);

    /* Add the mouse as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    keyboard_init();
    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = keyboard_read;
    lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
    lv_indev_set_group(kb_indev, g);
    mousewheel_init();
    static lv_indev_drv_t indev_drv_3;
    lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
    indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_3.read_cb = mousewheel_read;

    lv_indev_t *enc_indev = lv_indev_drv_register(&indev_drv_3);
    lv_indev_set_group(enc_indev, g);

    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    lv_obj_t *cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
}

/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data) {
    (void) data;

    while (1) {
        SDL_Delay(5);
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}
