#include "ui.hh"
#include "globals.hh"
#include "../imgui/imgui.h"
#include "../Modules/GUI.hh"
#include <Windows.h> 

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    ImGui::StyleColorsDark();

    if (window_pos.x == 0 && window_pos.y == 0) {
        RECT desktop_rect{};
        GetWindowRect(GetDesktopWindow(), &desktop_rect);
        screen_res = ImVec2(float(desktop_rect.right), float(desktop_rect.bottom));

        window_pos = ImVec2(
            (screen_res.x - window_size.x) * 0.5f,
            (screen_res.y - window_size.y) * 0.5f
        );
    }
}
void ui::render() {
    if (!globals::active) return;

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(0.9f);

    ImGui::Begin(window_title, &globals::active, window_flags);

    if (ImGui::BeginTabBar("GUI")) {

        if (ImGui::BeginTabItem("Combat")) {
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visual")) {
            static bool show_gui_settings = false;
            ImGui::Checkbox("GUI", &show_gui_settings);

            if (show_gui_settings) {
                ImGui::Separator();
                static int theme_idx = 0;
                static ImVec4 window_bg_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
                static float window_rounding = ImGui::GetStyle().WindowRounding;
                static float frame_rounding = ImGui::GetStyle().FrameRounding;
                static float frame_padding = ImGui::GetStyle().FramePadding.x;
                static float font_scale = ImGui::GetIO().FontGlobalScale;

                const char* themes[] = { "Blue", "Light", "Classic" };
                if (ImGui::Combo("Theme", &theme_idx, themes, IM_ARRAYSIZE(themes))) {
                    switch (theme_idx) {
                    case 0:
                        ImGui::StyleColorsDark();
                        {
                            ImVec4* colors = ImGui::GetStyle().Colors;
                            colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.15f, 0.3f, 1.0f);
                            colors[ImGuiCol_Header] = ImVec4(0.2f, 0.35f, 0.6f, 1.0f);
                            colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.45f, 0.7f, 1.0f);
                            colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.25f, 0.4f, 1.0f);
                        }
                        break;
                    case 1: ImGui::StyleColorsLight(); break;
                    case 2: ImGui::StyleColorsClassic(); break;
                    }
                    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = window_bg_color;
                }

                if (ImGui::ColorEdit4("Window Background", (float*)&window_bg_color)) {
                    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = window_bg_color;
                }

                if (ImGui::SliderFloat("Window Rounding", &window_rounding, 0.f, 15.f)) {
                    ImGui::GetStyle().WindowRounding = window_rounding;
                }

                if (ImGui::SliderFloat("Frame Rounding", &frame_rounding, 0.f, 15.f)) {
                    ImGui::GetStyle().FrameRounding = frame_rounding;
                }

                if (ImGui::SliderFloat("Frame Padding", &frame_padding, 0.f, 10.f)) {
                    ImGui::GetStyle().FramePadding = ImVec2(frame_padding, frame_padding);
                }

                if (ImGui::SliderFloat("Font Scale", &font_scale, 0.5f, 1.0f)) {
                    ImGui::GetIO().FontGlobalScale = font_scale;
                }
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc")) {
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();

    if (!globals::active) {
        PostQuitMessage(0);
    }
}

