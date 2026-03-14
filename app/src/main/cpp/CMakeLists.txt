cmake_minimum_required(VERSION 3.18)
project(myimgui)

# 设置 NDK 路径（从环境变量获取）
if(DEFINED ENV{ANDROID_NDK})
    set(ANDROID_NDK_PATH $ENV{ANDROID_NDK})
else()
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

# 添加 native_app_glue
add_library(native_app_glue STATIC
    ${ANDROID_NDK_PATH}/sources/android/native_app_glue/android_native_app_glue.c
)

add_library(myimgui SHARED native-lib.cpp)

target_include_directories(myimgui PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${ANDROID_NDK_PATH}/sources/android/native_app_glue
)

target_link_libraries(myimgui
    native_app_glue
    log
    android
    EGL
    GLESv3
    imgui
)
