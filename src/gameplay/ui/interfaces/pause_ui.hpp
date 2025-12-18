#pragma once

#include "deps.hpp"
#include "gameplay/ui/ui_layer.hpp"
#include "asset_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "timer.hpp"

namespace Game {

struct PauseUi : public UiLayer {

    PauseUi() {

        //std::println("pause ui made");

    }

    void update(double dt, Engine::Systems& sys) {

        sys.pause = true;
        //cooldown.update(dt);

    }

    void draw(RenderTexture canva) { 

        BeginTextureMode(canva); {

            DrawText("Pause", 100, 0, 3, WHITE);

        } EndTextureMode();
    }

    void process_input(Engine::Systems& sys) { 

        if (Engine::InputMan::is_event_active("pause") && sys.pause) {

            sys.pause = false;

            sys.ui->pop_interface();

        }


    }

};

}

