#include "asset_man.hpp"
#include "background_man.hpp"
#include "deps.hpp"

#include "gameplay/ui/interfaces/gameplay_ui.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "globals.hpp"
#include "gameplay/levels/action.hpp"
#include "input_man.hpp"
#include "gameplay/levels/levels.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "update_loop.hpp"
#include "draw_loop.hpp"
#include "control_schema.hpp"
#include "systems.hpp"
#include "winman.hpp"
#include "rocksdb/db.h"
#include "saving.hpp"

#include "gamecontrollerdb.h"

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    srand(time(NULL));

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, true);

    Engine::g_world_size = Vector2{320, 180};

    //load controller mappings from sdl database
    
    int output = SetGamepadMappings((char*)GAMECONTROLLERDB_DATA);
    std::println("mappings result: {}", output);


    double dt;

    InitAudioDevice();
    Engine::AssetMan::init();
    Engine::MusicMan::init();
    Engine::RenderMan::init(320, 180);
    Engine::BackgroundMan::init();

    Engine::AssetMan::get_texture("Connor_fodder2");

    Engine::InputMan::load_events(controls);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    Engine::Mode state = Engine::Mode::gameplay;
    Engine::GameState sys {state};

    sys.load("demo/demo.json");

    // Main game loop
    while (Engine::g_running)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";
        dt = GetFrameTime();
        Engine::InputMan::pull_events();

        if (WindowShouldClose()) 
            Engine::g_running = false;

        if (IsKeyPressed(KEY_ENTER)) 
            Engine::WinMan::toggle_fullscreen();

        if (IsKeyPressed(KEY_F3)) {

            Engine::g_debug = !Engine::g_debug;

        }

        if (IsKeyPressed(KEY_Y)) {
            sys.player->save_player(sys);
            sys.projectile->save_projectiles(sys);
            sys.enemy->save_enemies(sys);
            sys.level->save_level(sys);
            Engine::BackgroundMan::save_background(sys);
            std::println("saving ......");
        }

        if (IsKeyPressed(KEY_U)) {
            sys.player->load_player(sys);
            sys.projectile->load_projectiles(sys);
            sys.enemy->load_enemies(sys);
            sys.level->load_level(sys);
            Engine::BackgroundMan::load_background(sys);
            std::println("loading player....");

        }


        if (IsKeyPressed(KEY_I)) {

            Engine::AssetMan::cleanup();
            std::println("Cleaning assets");

        }

        Engine::WinMan::update_window();

        Engine::MusicMan::update();

        switch (state) {

            case Engine::Mode::gameplay: 
                {
                    gameplay_update_loop(dt, sys);
                    gameplay_draw_loop(sys);
                    break;
                }

            case Engine::Mode::level_editor:
                {

                    break;
                }
            case Engine::Mode::level_select:
                {

                    break;
                }

            case Engine::Mode::main_menu:
                {

                    break;
                }

        }

        //player_ui(sys);


        //----------------------------------------------------------------------------------
        // window.update_window();

        Engine::InputMan::flush_events();
    }

    return 0;
}


