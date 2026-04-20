#pragma once

#include "deps.hpp"

namespace Engine {

    struct Systems;

}

namespace Game {

struct UiLayer {

    virtual ~UiLayer() = default;

    virtual void update(double dt, Engine::Systems& sys) = 0;
    virtual void draw(RenderTexture canva) = 0;
    virtual void process_input(Engine::Systems& sys) = 0;
};

class UiMan {

public:
    
    UiMan(Vector2 canva_size) :
        ui_stack() {

            canva = LoadRenderTexture(canva_size.x, canva_size.y);
        }

    ~UiMan() {

        UnloadRenderTexture(canva);
    }


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
