#include "gui.hh"
#include <imgui.h>

namespace gui {

    static int themeIndex = 0;
    static ImVec4 windowBgColor = ImVec4(0.1f, 0.105f, 0.11f, 1.0f);

    void applyTheme(int idx) {
        switch (idx) {
        case 0: ImGui::StyleColorsDark(); break;
        case 1: ImGui::StyleColorsLight(); break;
        case 2: ImGui::StyleColorsClassic(); break;
        default: ImGui::StyleColorsDark(); break;
        }
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = windowBgColor;
    }

    void init() {
        applyTheme(themeIndex);
    }

    void renderSettings() {
        const char* themes[] = { "Blue", "Light", "Classic" };

        if (ImGui::Combo("Theme", &themeIndex, themes, IM_ARRAYSIZE(themes))) {
            applyTheme(themeIndex);
        }

        if (ImGui::ColorEdit4("Window Background", (float*)&windowBgColor)) {
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = windowBgColor;
        }
    }
}
