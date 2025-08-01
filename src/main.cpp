#include "deps.hpp"

#include "entity.hpp"
#include "gameplay/player/player_manager.hpp"
#include "globals.hpp"
#include "winman.hpp"
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

    engine::g_bullets = std::vector<std::unique_ptr<engine::Entity>>();

    engine::g_bullets.reserve(10);
    std::cout << "chec 1\n";

    game::PlayerMan::setup();

    double dt;

    game::assets::ship_tilemap = LoadTexture("assets/sprites/Space_pack/Space_VH.png");

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
