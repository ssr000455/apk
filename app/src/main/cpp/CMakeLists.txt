cmake_minimum_required(VERSION 3.18)
project(myimgui)

include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8
)
FetchContent_MakeAvailable(imgui)

add_library(myimgui SHARED native-lib.cpp)

target_link_libraries(myimgui
    log
    android
    EGL
    GLESv3
    imgui
)

target_include_directories(myimgui PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
