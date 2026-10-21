#pragma once

#include "deps.hpp"
#include "systems.hpp"

namespace Game {

struct UiLayer {

    virtual ~UiLayer() = default;

    virtual void update(double dt, Engine::GameState* sys) = 0;
    virtual void draw(RenderTexture canva) = 0;
};

}
