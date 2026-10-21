#include "asset_man.hpp"
#include "deps.hpp"

#include "game/game.hpp"
#include "globals.hpp"
#include "input_man.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "control_schema.hpp"
#include "winman.hpp"


#include "gamecontrollerdb.h"

void gameplay_loop(size_t save_slot, string level_path);
void main_menu_loop();

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    srand(time(NULL));
    SetTraceLogLevel(LOG_WARNING);

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, true);

    Engine::g_world_size = Vector2{320, 180};

    //load controller mappings from sdl database
    
    int output = SetGamepadMappings((char*)GAMECONTROLLERDB_DATA);
    //std::println("mappings result: {}", output);


    Engine::AssetMan::init();
    Engine::MusicMan::init();

    Engine::AssetMan::get_texture("Connor_fodder2");

    Engine::InputMan::load_events(controls);

    if(IsGamepadAvailable(0)) {
        std::cout << "gamepad 0 is ready\n";
    } else {
        std::cout << "gamepad not ready\n";

    }

    Game* game = new Game();

    // Main game loop
    while (Engine::g_running)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";

        Engine::WinMan::update_window();
        Engine::InputMan::pull_events();

        BeginDrawing();

        ClearBackground(BLACK);


        game->update();
        game->draw();

        DrawCircleV({400, 400}, 100, WHITE);

        EndDrawing();
        Engine::InputMan::flush_events();
    }

    return 0;
}


