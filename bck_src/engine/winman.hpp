#pragma once

#include "deps.hpp"

#include "raylib.h"
#include "rlImGui.h"
#include "globals.hpp"

namespace Engine {

class WinMan {

    inline static uint32_t m_width;
    inline static uint32_t m_height;
    inline static std::string m_title;
    inline static uint32_t m_display;

    inline static Vector2 m_prev_size;

public:
    static void init(const uint32_t width, const uint32_t height, std::string_view title, int target_fps, bool vsync) {

        m_width = width;
        m_height = height;
        m_title = std::string(title);

        if (vsync) SetConfigFlags(FLAG_VSYNC_HINT);
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        InitWindow(m_width, m_height, m_title.c_str());
        m_display = GetCurrentMonitor();

        SetTargetFPS(target_fps);


        rlImGuiSetup(true);
        m_prev_size = Vector2{(float)width, (float)height};

    }

    static uint32_t get_width() { return m_width; }
    static uint32_t get_height() { return m_height; }

    static void close() {

        std::cout << "window closed\n";
        CloseWindow();
    }

    static void toggle_fullscreen() {

        //the window size setting is there because imgui only updates its viewport when the window is resized, not when it goes fullscreen

        if (!IsWindowFullscreen()) {

            m_display = GetCurrentMonitor();

            m_prev_size.x = m_width;
            m_prev_size.y = m_height;

            m_width = GetMonitorWidth(m_display);
            m_height = GetMonitorHeight(m_display);

            SetWindowSize(m_width, m_height);

        } else {

            SetWindowSize(m_prev_size.x, m_prev_size.y);
            m_width = GetScreenWidth();
            m_height = GetScreenHeight();

        }


        ToggleFullscreen();
        //std::cout << m_width << "x" << m_height << '\n';

    }


    static void update_window() {

        m_width = GetScreenWidth();
        m_height = GetScreenHeight();

        if (WindowShouldClose()) 
            g_running = false;

        if (IsKeyPressed(KEY_ENTER)) 
            WinMan::toggle_fullscreen();

        if (IsKeyPressed(KEY_F3)) {

            g_debug = !g_debug;

        }

        //std::cout << m_width << "x" << m_height << '\n';
    }
};

}
