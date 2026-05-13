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

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;

enum struct Mode {

    gameplay

};

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
    char* mappings = LoadFileText("./assets/mappings/mapping.txt");
    SetGamepadMappings(mappings);
    UnloadFileText(mappings);


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

    Mode state = Mode::gameplay;
    Engine::GameState sys {"demo/demo.json"};

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


        if (IsKeyPressed(KEY_I)) {

            Engine::AssetMan::cleanup();
            std::println("Cleaning assets");

        }

        Engine::WinMan::update_window();

        Engine::MusicMan::update();

        switch (state) {

            case Mode::gameplay: {

                gameplay_update_loop(dt, sys);
                gameplay_draw_loop(sys);
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


