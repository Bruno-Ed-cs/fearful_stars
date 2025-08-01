#include "gameplay/player_manager.hpp"
#include "loops.hpp"
#include "globals.hpp"

void engine::draw_loop() {

        BeginTextureMode(g_canva);
        {

            ClearBackground(WHITE);
            DrawPixel(20, 20, RED);
            DrawPixel(21, 20, RED);
            DrawPixel(22, 20, RED);
            DrawPixel(23, 20, RED);

            DrawText("Congrats! You created your first window!", 27, 100, 1, LIGHTGRAY);


            for (int i = 0; i < engine::g_bullets.size(); i++) {

                engine::g_bullets[i]->draw();

            }
            
            auto p1 = game::PlayerManager::get_player();
            p1.draw();
            

        }
        EndTextureMode();

        BeginDrawing();

            ClearBackground(BLACK);


            //DrawTextureEx(canva.texture, {(float)window.get_width() / 2.0f, (float)window.get_height() / 2.0f}, 180.0f, 2.0f, WHITE);
            Rectangle source = { 0, 0, (float)g_canva.texture.width, (float)g_canva.texture.height * -1 };
            Rectangle dest = { 0, 0, (float)g_window->get_width(), (float)g_window->get_height()};
            Vector2 origin = { 0, 0 };
            DrawTexturePro(g_canva.texture, source, dest, origin, 0.0f, WHITE);
            


        EndDrawing();
}
