#pragma once

#include "deps.hpp"

namespace engine{

class WinMan {

    uint32_t m_width;
    uint32_t m_height;
    std::string m_title;
    uint32_t m_display;

public:
    WinMan(const uint32_t width, const uint32_t height, const std::string& title) :
    m_width(width), m_height(height) , m_title(title){

        InitWindow(m_width, m_height, m_title.c_str());
        m_display = GetCurrentMonitor();
    }

    uint32_t get_width() { return m_width; }
    uint32_t get_height() { return m_height; }

    ~WinMan() {

        std::cout << "window closed\n";
        CloseWindow();
    }

    void toggle_fullscreen() {


        if (!IsWindowFullscreen()) {

            m_display = GetCurrentMonitor();

            m_width = GetMonitorWidth(m_display);
            m_height = GetMonitorHeight(m_display);

        } else {
            m_width = GetScreenWidth();
            m_height = GetScreenHeight();
        }

        ToggleFullscreen();
        //std::cout << m_width << "x" << m_height << '\n';

    }

    void update_window() {

        m_width = GetScreenWidth();
        m_height = GetScreenHeight();

        std::cout << m_width << "x" << m_height << '\n';
    }
};

}
