#include <android_native_app_glue.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <unistd.h>

#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ImGui", __VA_ARGS__)

void android_main(struct android_app* app) {
    app->onAppCmd = [](struct android_app* app, int32_t cmd) {
        if (cmd == APP_CMD_INIT_WINDOW) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

            ImGui::StyleColorsDark();

            ImGui_ImplAndroid_Init(app->window);
            ImGui_ImplOpenGL3_Init("#version 300 es");

            bool running = true;
            while (running) {
                int events;
                struct android_poll_source* source;
                while (ALooper_pollAll(0, NULL, &events, (void**)&source) >= 0) {
                    if (source) source->process(app, source);
                }

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplAndroid_NewFrame();
                ImGui::NewFrame();

                ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
                ImGui::Begin("ImGui on Android", nullptr);
                ImGui::Text("Hello, Android!");
                ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
                if (ImGui::Button("Close")) {
                    running = false;
                }
                ImGui::End();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW));
                usleep(16000);
            }

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplAndroid_Shutdown();
            ImGui::DestroyContext();
        }
    };

    while (1) {
        int events;
        struct android_poll_source* source;
        while (ALooper_pollAll(-1, NULL, &events, (void**)&source) >= 0) {
            if (source) source->process(app, source);
        }
    }
}
