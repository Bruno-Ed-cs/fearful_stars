#include "gameplay/entity.hpp"
#include "gameplay/projectile.hpp"
#include "globals.hpp"
#include "raylib.h"
#include "winman.hpp"
#include "gameplay/player.hpp"
#include <cassert>
#include <memory>
#include <vector>
#include "loops.hpp"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    engine::g_window = std::make_unique<engine::WinMan>(1280, 720, "Fearful Stars");

    std::cout << "window loaded\n";
    engine::g_canva = LoadRenderTexture(320, 180);

    std::cout << "canva loaded\n";



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    engine::g_bullets = std::vector<std::unique_ptr<game::Entity>>();

    engine::g_bullets.reserve(10);
    std::cout << "chec 1\n";

    engine::g_bullets.emplace_back(std::make_unique<game::Player>(Vector2{0, 0}));
    std::cout << "chec2\n";

    double dt;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        std::cout << "check 3\n";
        dt = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) 
            engine::g_window->toggle_fullscreen();

        engine::update_loop(dt);
        engine::draw_loop();
        //----------------------------------------------------------------------------------
       // window.update_window();
        
    }

    return 0;
}
