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
    SetTraceLogLevel(LOG_ERROR);

    //    SetConfigFlags(FLAG_VSYNC_HINT);
    // Initialization
    //--------------------------------------------------------------------------------------

    Engine::WinMan::init(1280, 720, "Fearful Stars", 0, false);

    Engine::g_world_size = Vector2{320, 180};

    //load controller mappings from sdl database
    
    int output = SetGamepadMappings((char*)GAMECONTROLLERDB_DATA);
    //std::println("mappings result: {}", output);

    std::println("game size: {}", sizeof(Game));

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
    RenderTexture2D view = LoadRenderTexture(Engine::g_world_size.x, Engine::g_world_size.y);

    // Main game loop
    while (Engine::g_running)    // Detect window close button or ESC key
    {
        //std::cout << "check 3\n";

        Engine::WinMan::update_window();
        Engine::InputMan::pull_events();

        game->update();

        BeginDrawing();

        ClearBackground(BLACK);

        BeginTextureMode(view);

        ClearBackground(BLACK);
        game->draw();

        EndTextureMode();

        Rectangle dest = {0, 0, (float)Engine::WinMan::get_width(), (float)Engine::WinMan::get_height()};
        DrawTexturePro(view.texture, {0, 0, Engine::g_world_size.x, -Engine::g_world_size.y}, dest, {0, 0}, 0.0, WHITE);

        DrawFPS(0, 0);

        EndDrawing();
        Engine::InputMan::flush_events();
    }

    UnloadRenderTexture(view);

    return 0;
}


