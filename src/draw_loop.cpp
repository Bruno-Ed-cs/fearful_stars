#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "imgui.h"
#include "loops.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "winman.hpp"


void engine::draw_loop() {

    BeginTextureMode(g_canva);
    {

        ClearBackground(WHITE);
        DrawPixel(20, 20, RED);
        DrawPixel(21, 20, RED);
        DrawPixel(22, 20, RED);
        DrawPixel(23, 20, RED);

        DrawText("Congrats! You created your first window!", 27, 100, 1, LIGHTGRAY);


        game::ProjectileMan::draw();
        auto& p1 = game::PlayerMan::get_player();
        p1.draw();


    }
    EndTextureMode();

    BeginDrawing();
    {

        ClearBackground(BLACK);


        //DrawTextureEx(canva.texture, {(float)window.get_width() / 2.0f, (float)window.get_height() / 2.0f}, 180.0f, 2.0f, WHITE);
        Rectangle source = { 0, 0, (float)g_canva.texture.width, (float)g_canva.texture.height * -1 };
        Rectangle dest = { 0, 0, (float)g_window->get_width(), (float)g_window->get_height()};
        Vector2 origin = { 0, 0 };
        DrawTexturePro(g_canva.texture, source, dest, origin, 0.0f, WHITE);

        if (engine::g_debug) {

        rlImGuiBegin();

        //ImGui::ShowDemoWindow();

        ImGui::SetNextWindowPos({0, 0});
        ImGui::Begin("FPS Monitor", NULL, ImGuiWindowFlags_NoResize);
        {

            ImGui::Text("FPS: %d", GetFPS());
            ImGui::Text("Frametime %f ms", GetFrameTime());

        }
        ImGui::End();

        game::ProjectileMan::debug();
        game::PlayerMan::debug();

        rlImGuiEnd();
        }

    }        



    EndDrawing();
}
