#include "ui_man.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "render_man.hpp"

using namespace Game;

UiMan::UiMan(Vector2 canva_size) :
ui_stack() {

    canva = LoadRenderTexture(canva_size.x, canva_size.y);
}

UiMan::~UiMan() {

    UnloadRenderTexture(canva);
}

void UiMan::draw() {

    BeginTextureMode(canva);

        ClearBackground(BLANK);

    EndTextureMode();

    for (auto& interface: ui_stack) {

        interface->draw(canva);
    }

    //send to renderman
    auto source = Rectangle{0, 0, (float)canva.texture.width, (float)canva.texture.height};
    auto view = source;
    source.height *= -1;

    Engine::RenderMan::send_texture(Engine::RenderMan::Plane::ui , canva.texture, view, source);
}

void UiMan::update(double dt, Engine::GameState* sys) {

    if (ui_stack.empty()) return;
    ui_stack.back()->update(dt, sys);

    // for (auto& layer : ui_stack) {
    //
    //     layer->update(dt, sys);
    // }

}


void UiMan::stack_interface(std::unique_ptr<UiLayer> layer) {

    ui_stack.push_back(std::move(layer));

}

void UiMan::pop_interface() {

    if (ui_stack.size() > 0) 
        ui_stack.pop_back();

}

void UiMan::clear_screen() {

    ui_stack.clear();

}

uint32_t UiMan::selector(uint32_t current, uint32_t limit) {

    uint32_t final = current;

    if (final > limit) 
        final = limit;

    if (Engine::InputMan::is_event_active("ui_up")) {
        final--;
        if (final < 1) 
            final = limit;
    }

    if (Engine::InputMan::is_event_active("ui_down")) {
        final++;
        if (final > limit)
            final = 1;
    }

    return final;

}
