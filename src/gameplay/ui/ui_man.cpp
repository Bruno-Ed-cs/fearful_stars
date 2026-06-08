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

uint32_t UiMan::selector(uint32_t current, uint32_t limit, uint32_t cols) {

    uint32_t final = current;
    assert(cols != 0);
    uint32_t partition = (limit +1) / cols;
    uint32_t cur_col = current / partition;

    if (final > limit) 
        final = limit;

    std::println("partition_size = {}\ncur_col = {}\ncols = {}\n", partition, cur_col, cols);
    if (Engine::InputMan::is_event_active("ui_up")) {

        final--;
        if (final == ((cur_col -1) * partition)) {
            final += partition -1;
        }

    }

    if (Engine::InputMan::is_event_active("ui_down")) {

        if (final == ((cur_col +1) * partition) -1) {
            final = cur_col * partition;

        } else {

            final++;
        }
    }

    if (Engine::InputMan::is_event_active("ui_left")) {

        if (cur_col == 0) {
            final += partition * (cols - 1);
        } else {
            final -= partition;
        }
    }

    if (Engine::InputMan::is_event_active("ui_right")) {
        if (cur_col == cols -1) {
            final -= partition * (cols - 1);
        } else {
            final += partition;
        }
    }

    std::println("selected: {}", final);

    return final;

}
