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
    void update(double dt, Engine::GameState* sys = nullptr);
    void stack_interface(std::unique_ptr<UiLayer> layer);
    void pop_interface();
    void clear_screen();
    static uint32_t selector(uint32_t current, uint32_t limit, uint32_t cols = 1);

private:

    std::vector<std::unique_ptr<UiLayer>> ui_stack;
    RenderTexture canva;
};

}
