#include "deps.hpp"

#include "gameplay/player/player_manager.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "raylib.h"
#include "loops.hpp"
#include "control_schema.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"

#include "imgui.h"
#include "rlImGui.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Engine::g_window = std::make_unique<Engine::WinMan>(1280, 720, "Fearful Stars");


    Engine::g_canva_size = Vector2{320, 180};
    Engine::g_canva = LoadRenderTexture(Engine::g_canva_size.x, Engine::g_canva_size.y);

    Game::PlayerMan::setup();

    double dt;

    Game::Assets::ship_tilemap = LoadTexture("assets/sprites/Space_pack/Space_VH.png");

    Engine::InputMan::load_events(controls);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    Game::EnemyMan enemy_man = Game::EnemyMan();

    auto enemy = std::make_unique<Game::BasicEnemy>();
    enemy_man.insert_enemy(std::move(enemy));


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        Engine::InputMan::pull_events();

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) 
            Engine::g_window->toggle_fullscreen();

        if (IsKeyPressed(KEY_F3)) {

            Engine::g_debug = !Engine::g_debug;

        }

        Engine::update_loop(dt, enemy_man);
        Engine::draw_loop(enemy_man);

        //----------------------------------------------------------------------------------
        // window.update_window();

        Engine::InputMan::flush_events();
    }

    rlImGuiShutdown();
    //Engine::InputMan::close();

    return 0;
}
