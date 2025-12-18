#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "systems.hpp"

namespace Game {

class UiMan {

public:
    
    UiMan(Vector2 canva_size);
    ~UiMan();

    void draw();
    void update(double dt, Engine::Systems& sys);
    void stack_interface(std::unique_ptr<UiLayer> layer);
    void pop_interface();
    void clear_screen();

private:

    std::vector<std::unique_ptr<UiLayer>> ui_stack;
    RenderTexture canva;
};

}
