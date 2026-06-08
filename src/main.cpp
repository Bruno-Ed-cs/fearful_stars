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
#include "control_schema.hpp"
#include "systems.hpp"
#include "winman.hpp"
#include "rocksdb/db.h"
#include "saving.hpp"

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

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, true);

    Engine::g_world_size = Vector2{320, 180};

    //load controller mappings from sdl database
    
    int output = SetGamepadMappings((char*)GAMECONTROLLERDB_DATA);
    std::println("mappings result: {}", output);


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


    // Main game loop
    while (Engine::g_running)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";

        Engine::WinMan::update_window();
        Engine::MusicMan::clean();

        switch (Engine::app_state) {

            case Engine::AppState::gameplay: 
                {
                    gameplay_loop(Engine::save_slot, Engine::level_path);
                    break;
                }

            case Engine::AppState::level_editor:
                {

                    break;
                }
            case Engine::AppState::level_select:
                {

                    break;
                }

            case Engine::AppState::main_menu:
                {
                    main_menu_loop();
                    break;
                }

        }

    }

    return 0;
}


