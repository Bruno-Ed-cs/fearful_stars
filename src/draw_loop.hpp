#pragma once 

#include "background_man.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/player/player_manager.hpp"
#include "render_man.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "systems.hpp"
#include "winman.hpp"
#include "asset_man.hpp"

auto font = Engine::AssetMan::get_font("EXEPixelPerfect");

void draw_loop(Engine::Systems& sys) {

    sys.player->draw();
    sys.projectile->draw();
    sys.enemy->draw();
    Engine::BackgroundMan::draw();


    Engine::RenderMan::render_to_canva();

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
}
