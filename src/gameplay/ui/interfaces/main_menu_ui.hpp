#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"

namespace Game {

struct MainMenuUi: public UiLayer {

    RenderTexture ui;
    uint32_t cur_button = 0;
    UiMan& manager;

    MainMenuUi(UiMan& manager):
    manager(manager){

        auto size = Engine::RenderMan::canva_size();
        ui = LoadRenderTexture(size.x, size.y);

    }

    void update(double dt, Engine::GameState* sys) {
        auto size = Engine::RenderMan::canva_size();
       BeginTextureMode(ui); {

           DrawRectangleGradientV(0, 0, size.x, size.y, BLACK, BLUE);

        } EndTextureMode();
    }

    void draw(RenderTexture canva) {

        Engine::RenderMan::send_texture(
                Engine::RenderMan::Plane::ui,
                ui.texture,
                Rectangle {0, 0, (float)ui.texture.width, (float)ui.texture.height},
                Rectangle {0, 0, (float)ui.texture.width, (float)ui.texture.height * -1});
    }


    ~MainMenuUi() {
        UnloadRenderTexture(ui);

    }

};

}

