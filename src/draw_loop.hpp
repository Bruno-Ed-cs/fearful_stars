#pragma once 

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

    BeginTextureMode(Engine::g_canva);
    {

        ClearBackground(WHITE);

        DrawText("Congrats! You created your first window!", 27, 100, 1, LIGHTGRAY);


        sys.projectile->draw();
        sys.player->draw();
        sys.enemy->draw();

        DrawTextEx(*font, "This fuking works", Vector2{50,50}, 10.0, 1.0, BLACK);

    }
    EndTextureMode();

    BeginDrawing();
    {

        ClearBackground(BLACK);


        //DrawTextureEx(canva.texture, {(float)window.get_width() / 2.0f, (float)window.get_height() / 2.0f}, 180.0f, 2.0f, WHITE);
        Rectangle source = { 0, 0, (float)Engine::g_canva.texture.width, (float)Engine::g_canva.texture.height * -1 };
        Rectangle dest = { 0, 0, (float)Engine::WinMan::get_width(), (float)Engine::WinMan::get_height()};
        Vector2 origin = { 0, 0 };
        DrawTexturePro(Engine::g_canva.texture, source, dest, origin, 0.0f, WHITE);

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

        sys.projectile->debug();
        sys.player->debug();

        rlImGuiEnd();
        }

    }        



    EndDrawing();
}
