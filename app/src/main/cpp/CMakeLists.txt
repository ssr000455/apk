cmake_minimum_required(VERSION 3.18)
project(myimgui)

# 设置 NDK 路径
if(DEFINED ENV{ANDROID_NDK})
    set(ANDROID_NDK_PATH $ENV{ANDROID_NDK})
else()
    set(ANDROID_NDK_PATH ${ANDROID_NDK})
endif()

message(STATUS "Using NDK: ${ANDROID_NDK_PATH}")

# 下载 ImGui
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

# 添加 native_app_glue
add_library(native_app_glue STATIC
    ${ANDROID_NDK_PATH}/sources/android/native_app_glue/android_native_app_glue.c
)

# 添加主库
add_library(myimgui SHARED native-lib.cpp)

# 将 ImGui 源文件直接添加到 myimgui 中
target_sources(myimgui PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_android.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# 包含目录
target_include_directories(myimgui PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${ANDROID_NDK_PATH}/sources/android/native_app_glue
)

# 链接库
target_link_libraries(myimgui
    native_app_glue
    log
    android
    EGL
    GLESv3
)
