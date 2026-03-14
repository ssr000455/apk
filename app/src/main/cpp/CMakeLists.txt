cmake_minimum_required(VERSION 3.18)
project(myimgui)

set(ANDROID_NDK_PATH $ENV{ANDROID_NDK})
if(NOT ANDROID_NDK_PATH)
    set(ANDROID_NDK_PATH ${ANDROID_NDK})
endif()
message(STATUS "Using NDK: ${ANDROID_NDK_PATH}")

include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

add_library(native_app_glue STATIC
    ${ANDROID_NDK_PATH}/sources/android/native_app_glue/android_native_app_glue.c
)

add_library(myimgui SHARED native-lib.cpp)

target_sources(myimgui PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_android.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(myimgui PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${ANDROID_NDK_PATH}/sources/android/native_app_glue
)

target_link_libraries(myimgui
    native_app_glue
    log
    android
    EGL
    GLESv3
)
