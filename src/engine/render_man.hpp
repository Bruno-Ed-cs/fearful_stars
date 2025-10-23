#pragma once
#include "deps.hpp"

namespace Engine {

struct RenderElement {

    Texture source;
    Rectangle render_view;
    Rectangle source_view;
    int z_index = 0;
    double rotation = 0.0;
//    std::optional<Shader> effect;
//    std::function<void(RenderElement*, double)> script = nullptr;
};

class RenderMan {
    
    //send sprites and location on canva
    //make background
    //make background elements move
    //have z levels
    //
    //buffer 
    //have the rendering to the window a winman thing
    //move the canva to here

public:
    static void send_back(Texture sprite, Rectangle render_view, Rectangle source_view, int z_index = 0, double rotation = 0);
    static void send_front(Texture sprite, Rectangle render_view, Rectangle source_view, int z_index = 0, double rotation = 0);
    static void send_middle(Texture sprite, Rectangle render_view, Rectangle source_view, int z_index = 0, double rotation = 0);

    static void init(int canva_wid, int canva_hei);
    static void draw_to_window();
    
    static Vector2 canva_size();

private:

    using buffer = std::vector<RenderElement>;

    static void render_to_canva();

    inline static bool s_initialized;

    inline static RenderTexture s_canva;
    inline static buffer s_background;
    inline static buffer s_middleground;
    inline static buffer s_foreground;

};

}
