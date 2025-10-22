#pragma once
#include "deps.hpp"
#include "raylib.h"
#include <optional>
#include <vector>

namespace Engine {

struct RenderElement {

    Texture source;
    Rectangle render_view;
    Rectangle source_view;
    int z_index;
    std::optional<Shader> effect;
    std::function<void(RenderElement*, double)> script = nullptr;

    RenderElement(Texture source, Rectangle render_view, Rectangle source_view,
                  int z_index = 0,
                  std::optional<Shader> effect = std::nullopt, 
                  std::function<void(RenderElement*, double)> script = nullptr) :
    source(source), render_view(render_view), source_view(source_view), z_index(z_index), effect(effect), script(script) {};
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
private:

    using buffer = std::vector<RenderElement>;

    static RenderMan instance;
    RenderMan();

    buffer background;
    buffer middleground;
    buffer foreground;

};

}
