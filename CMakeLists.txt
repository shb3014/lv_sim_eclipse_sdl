cmake_minimum_required(VERSION 3.10)
project(lvgl)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE INCLUDES "lv_drivers/*.h" "lv_demos/*.h"  "lvgl/*.h"  "./*.h" )
file(GLOB_RECURSE SOURCES  "lv_drivers/*.c" "lv_demos/*.c"  "lvgl/*.c" "ui/*.cpp" "utils/*.cpp" "drivers/*.cpp" "text/*.c" "tool/*.cpp")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
SET(CMAKE_CXX_FLAGS "-O3")

add_definitions(-DLV_SIM)

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(main main.cpp mouse_cursor_icon.c ${SOURCES} ${INCLUDES} ui/UITime.cpp ui/UITime.h ui/UIDate.cpp ui/UIDate.h ui/UIDoubleProgress.cpp ui/UIDoubleProgress.h ui/UIActionBox.cpp ui/UIActionBox.h ui/UILoading.cpp ui/UILoading.h ui/UIQrCode.cpp ui/UIQrCode.h ui/UIPlantStatus.cpp ui/UIPlantStatus.h tool/sys.cpp tool/sys.h ui/UITest.cpp ui/UITest.h ui/UIText.cpp ui/UIText.h ui/Components.cpp ui/Components.h ui/UIFluid.cpp ui/UIFluid.h)
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
target_link_libraries(main PRIVATE SDL2 )
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main)
