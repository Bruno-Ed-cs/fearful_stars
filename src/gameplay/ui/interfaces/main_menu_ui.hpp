#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player.hpp"
#include "globals.hpp"
#include "gameplay/ui/elements/button.hpp"
#include "raylib.h"
#include "gameplay/ui/ui_man.hpp"
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
           std::string title = "Fearful\n Stars";
           int title_height = 40;
           int title_size = MeasureText(title.c_str(), title_height);

           DrawText(title.c_str(), (size.x - title_size) / 2, 5, title_height, WHITE);

           Rectangle play = {size.x /2 - 55/2, size.y / 2 + 20, 55, 21};
           Rectangle quit = {size.x /2 - 55/2, play.y + 21 + 5, 55, 21};

           cur_button = UiMan::selector(cur_button, 1);

           if (Button::basic(play, cur_button, 0, "Play")) {
               Engine::app_state = Engine::AppState::gameplay;

           }

           if (Button::basic(quit, cur_button, 1, "Quit")) {

               Engine::g_running = false;

           }

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

