#pragma once 

#include "background_man.hpp"
#include "gameplay/enemy/enemy.hpp"
#include "gameplay/player/player.hpp"
#include "render_man.hpp"
#include "gameplay/projectile/projectile.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "globals.hpp"
#include "systems.hpp"
#include "winman.hpp"
#include "asset_man.hpp"


void gameplay_draw_loop(Engine::GameState& sys) {

    BeginDrawing();
    {

        ClearBackground(BLACK);

        if (Engine::g_debug) {

            sys.projectile->debug_world();
            sys.enemy->debug_world();
            sys.player->debug_world();
        }

        Engine::RenderMan::draw_to_window();

        if (Engine::g_debug) {

        rlImGuiBegin();

        //ImGui::ShowDemoWindow();

        ImGui::SetNextWindowPos({0, 0});
        ImGui::Begin("FPS Monitor", NULL, ImGuiWindowFlags_NoResize);
        {

            ImGui::Text("FPS: %d", GetFPS());
            ImGui::Text("Frametime %f ms", GetFrameTime());

        }
        ImGui::End();

        sys.projectile->debug_ui();
        sys.enemy->debug_ui();
        sys.player->debug_ui();

        rlImGuiEnd();
        }

    }        



    EndDrawing();

    sys.player->draw();
    sys.projectile->draw();
    sys.enemy->draw();
    sys.ui->draw();
    Engine::BackgroundMan::draw();

    Engine::RenderMan::render_to_canva();
}
