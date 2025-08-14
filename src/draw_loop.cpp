#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
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
        DrawFPS(20, 0);
ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2(
                static_cast<float>(GetScreenWidth()),
                static_cast<float>(GetScreenHeight())
            );
        rlImGuiBegin();
   // Optional: Add a simple control window
            ImGui::Begin("Fullscreen Control");
            ImGui::Text("Press F11 to toggle fullscreen");
            ImGui::Text("Current mode: %s", IsWindowFullscreen() ? "Fullscreen" : "Windowed");
            if (ImGui::Button("Toggle Fullscreen")) {
                g_window->toggle_fullscreen();
            }
            ImGui::End();

        ImGui::ShowDemoWindow();


        rlImGuiEnd();

    }        



    EndDrawing();
}
