#include <android_native_app_glue.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ImGui", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "ImGui", __VA_ARGS__)

static bool g_Initialized = false;

static void handle_cmd(struct android_app* app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            LOGI("APP_CMD_INIT_WINDOW");
            if (app->window != NULL) {
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
                ImGui::StyleColorsDark();

                if (!ImGui_ImplAndroid_Init(app->window)) {
                    LOGE("ImGui_ImplAndroid_Init failed");
                    return;
                }
                if (!ImGui_ImplOpenGL3_Init("#version 300 es")) {
                    LOGE("ImGui_ImplOpenGL3_Init failed");
                    return;
                }
                g_Initialized = true;
                LOGI("ImGui initialized successfully");
            }
            break;
        case APP_CMD_TERM_WINDOW:
            LOGI("APP_CMD_TERM_WINDOW");
            if (g_Initialized) {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplAndroid_Shutdown();
                ImGui::DestroyContext();
                g_Initialized = false;
            }
            break;
    }
}

void android_main(struct android_app* app) {
    app_dummy();
    LOGI("android_main started");
    app->onAppCmd = handle_cmd;

    while (1) {
        int events;
        struct android_poll_source* source;
        while (ALooper_pollAll(0, NULL, &events, (void**)&source) >= 0) {
            if (source != NULL) {
                source->process(app, source);
            }
        }
        if (g_Initialized) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplAndroid_NewFrame();
            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
            ImGui::Begin("ImGui on Android", nullptr);
            ImGui::Text("Hello, Android!");
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            if (ImGui::Button("Close")) {
                ANativeActivity_finish(app->activity);
            }
            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW));
        }
    }
}
