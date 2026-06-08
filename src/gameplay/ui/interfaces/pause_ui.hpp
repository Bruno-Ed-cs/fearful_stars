#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "gameplay/ui/elements/button.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "timer.hpp"

namespace Game {

struct PauseUi : public UiLayer {

    RenderTexture ui;
    uint32_t cur_button = 0;
    UiMan& manager;

    PauseUi(UiMan& manager):
    manager(manager){

        //std::println("pause ui made");
        auto size = Engine::RenderMan::canva_size();
        ui = LoadRenderTexture(size.x, size.y);

    }

    void update(double dt, Engine::GameState* sys) {

        assert(sys != nullptr);
        
        sys->pause = true;
 
        auto canva_size = Engine::RenderMan::canva_size();
        cur_button = UiMan::selector(cur_button, 2);

        Rectangle box = {canva_size.x /2 - 40, canva_size.y / 2 - 50, 70, 100};
        Rectangle continue_button = {box.x + 5, box.y + 20, 60, 21};
        Rectangle quit_button = {box.x + 5, box.y + 45, 60, 21};
        Rectangle menu_button = {box.x + 5, box.y + 70, 60, 21};

        BeginTextureMode(ui); {

            DrawRectangleRec(box, BLACK);
            DrawRectangleLinesEx(box, 1, BLUE);

            if (Button::basic(continue_button, cur_button, 0, "Continue")) {
                sys->pause = false;
                manager.pop_interface();
            }
                
            if (Button::basic(quit_button, cur_button, 1, "Quit")) 
                Engine::g_running = false;

            if (Button::basic(menu_button, cur_button, 2, "Main menu")) {

                Engine::app_state = Engine::AppState::main_menu;
            }

            int text_width = MeasureText("Pause", 3);
            DrawText("Pause", box.x + (box.width - text_width) / 2, box.y + 4, 3, WHITE);

        } EndTextureMode();
        //cooldown.update(dt);

        if (Engine::InputMan::is_event_active("pause")) {

            sys->pause = false;
            manager.pop_interface();
            return;

        }

        if (Engine::InputMan::is_event_active("ui_deny")) {

            sys->pause = false;
            manager.pop_interface();
            return;

        }

    }

    void draw(RenderTexture canva) {
        auto canva_size = Engine::RenderMan::canva_size();
        Engine::RenderMan::send_texture(
                Engine::RenderMan::Plane::ui,
                ui.texture,
                Rectangle {0, 0, (float)ui.texture.width, (float)ui.texture.height},
                Rectangle {0, 0, (float)ui.texture.width, (float)ui.texture.height * -1});
    }


    ~PauseUi() {

        UnloadRenderTexture(ui);

    }

};

}

