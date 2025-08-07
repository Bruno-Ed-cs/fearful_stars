#include "deps.hpp"

#include "entity.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "winman.hpp"
#include "loops.hpp"
#include "control_schema.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------
    
    engine::g_window = std::make_unique<engine::WinMan>(1280, 720, "Fearful Stars");

    engine::g_canva_size = Vector2{320, 180};
    engine::g_canva = LoadRenderTexture(engine::g_canva_size.x, engine::g_canva_size.y);



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    game::PlayerMan::setup();

    double dt;

    game::assets::ship_tilemap = LoadTexture("assets/sprites/Space_pack/Space_VH.png");

    engine::InputMan::load_events(controls);

    if (IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        engine::InputMan::pull_events();

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

        engine::InputMan::flush_events();
    }

    //engine::InputMan::close();

    return 0;
}
