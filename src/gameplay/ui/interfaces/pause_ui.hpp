#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "gameplay/ui/elements/button.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "systems.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "timer.hpp"

namespace Game {

struct PauseUi : public UiLayer {

    RenderTexture ui;

    PauseUi() {

        //std::println("pause ui made");
        auto size = Engine::RenderMan::canva_size();
        ui = LoadRenderTexture(size.x, size.y);

    }

    void update(double dt, Engine::GameState& sys) {

        sys.pause = true;
        //cooldown.update(dt);

    }

    void draw(RenderTexture canva) { 

        size_t cur_button = 0;
        Rectangle b1 = {10, 10, 50, 20};

        BeginTextureMode(canva); {

            Button::basic(b1, cur_button, 1, "Continue");
            DrawText("Pause", 100, 0, 3, WHITE);

        } EndTextureMode();
    }

    void process_input(Engine::GameState& sys) { 

        if (Engine::InputMan::is_event_active("pause") && sys.pause) {

            sys.pause = false;

            sys.ui->pop_interface();

        }


    }

    ~PauseUi() {

        UnloadRenderTexture(ui);

    }

};

}

