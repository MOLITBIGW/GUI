#pragma once
#include <d3d9.h>
#include "../imgui/imgui.h"

namespace ui {
    void init(LPDIRECT3DDEVICE9 device);
    void render();

    inline LPDIRECT3DDEVICE9 dev = nullptr;
    inline const char* window_title = "GUI";

    inline ImVec2 screen_res{ 0, 0 };
    inline ImVec2 window_pos{ 0, 0 };
    inline ImVec2 window_size{ 400, 300 };
    inline DWORD window_flags = ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoScrollbar;
}
