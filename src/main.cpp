#include "raylib.h"
#include "libs/winman.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    engine::WinMan window(1280, 720, "Fearful Stars");
    auto canva = LoadRenderTexture(320, 180);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Texture2D connortt = LoadTexture("assets/sprites/Connor_fodder2.png");
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) 
            window.toggle_fullscreen();

        BeginTextureMode(canva);
        {

            ClearBackground(WHITE);
            DrawPixel(20, 20, RED);
            DrawPixel(21, 20, RED);
            DrawPixel(22, 20, RED);
            DrawPixel(23, 20, RED);

            DrawText("Congrats! You created your first window!", 27, 100, 1, LIGHTGRAY);

            DrawTextureEx(connortt, {100, 70}, 0.0f, 1.0f, WHITE);

        }
        EndTextureMode();

        BeginDrawing();

            ClearBackground(BLACK);


            //DrawTextureEx(canva.texture, {(float)window.get_width() / 2.0f, (float)window.get_height() / 2.0f}, 180.0f, 2.0f, WHITE);
            Rectangle source = { 0, 0, (float)canva.texture.width, (float)canva.texture.height * -1 };
            Rectangle dest = { 0, 0, (float)window.get_width(), (float)window.get_height()};
            Vector2 origin = { 0, 0 };
            DrawTexturePro(canva.texture, source, dest, origin, 0.0f, WHITE);
            


        EndDrawing();
        //----------------------------------------------------------------------------------
       // window.update_window();
        
    }

    return 0;
}
