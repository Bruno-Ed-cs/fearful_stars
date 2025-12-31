#include "asset_man.hpp"
#include "background_man.hpp"
#include "deps.hpp"

#include "gameplay/levels/level_actions/play_ost.hpp"
#include "gameplay/ui/interfaces/gameplay_ui.hpp"
#include "gameplay/ui/ui_man.hpp"
#include "gameplay/levels/level_actions/player_move_action.hpp"
#include "gameplay/levels/level_actions/spawn_upgrade_action.hpp"
#include "gameplay/player/player_manager.hpp"
#include "gameplay/projectile/projectile_manager.hpp"
#include "globals.hpp"
#include "gameplay/levels/i_action.hpp"
#include "input_man.hpp"
#include "gameplay/levels/level_actions/spawn_enemies_action.hpp"
#include "gameplay/levels/level_actions/wait_action.hpp"
#include "gameplay/levels/level_actions/wave_end_action.hpp"
#include "gameplay/levels/levels.hpp"
#include "music_man.hpp"
#include "raylib.h"
#include "render_man.hpp"
#include "update_loop.hpp"
#include "draw_loop.hpp"
#include "control_schema.hpp"
#include "gameplay/enemy/enemy_man.hpp"
#include "gameplay/enemy/basic/basic_enemy.hpp"
#include "systems.hpp"
#include "winman.hpp"

using string = std::string;
using AssRef = Engine::AssetMan::Ref::Type;

void make_background() {

    // Distribute 15 background elements across 320x180 screen
    // Group 1: Column 3 sprites (3 elements)
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{50, 30}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{270, 150}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 3, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{160, 90}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    // Group 2: Column 2 sprites (4 elements)  
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{240, 40}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{80, 140}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{300, 100}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 2, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{20, 50}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    // Group 3: Column 1 sprites (4 elements)
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{100, 20}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{220, 160}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{40, 100}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{16 * 1, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{280, 60}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

    // Group 4: Column 0 sprites (4 elements)
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{140, 120}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{60, 160}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{200, 30}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);
    Engine::BackgroundMan::create_element(Engine::AssetMan::get_texture("earthBackgroudeErased"), Rectangle{0, 0, 16, 16}, Rectangle{0, 0, 16, 16}, Game::Position(Vector2{300, 170}), 0, 0, 0, Engine::BackgroundElement::Mode::stay);

}



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

    Engine::Systems sys{};

    //make_level(sys);
    sys.level->load_level("demo/demo.json");
    sys.player->init_player({90, 60});
    sys.ui->stack_interface(std::make_unique<Game::GameplayUi>());
    make_background();

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

        update_loop(dt, sys);

        //player_ui(sys);
        draw_loop(sys);


        //----------------------------------------------------------------------------------
        // window.update_window();

        Engine::InputMan::flush_events();
    }

    return 0;
}


